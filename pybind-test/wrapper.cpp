#include <pybind11/embed.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include "fibonacci.h"
#include "response.h"

namespace py = pybind11;
using namespace std::chrono_literals;

PYBIND11_EMBEDDED_MODULE( aiges_sdk, m )
{
	m.doc() = "pybind11 example plugin for fibonacci";

	m.def( "fibonacci", &fibonacci, "Fibonacci function using C++" );
	py::class_<ResponseData> responseData( m, "ResponseData", py::buffer_protocol() );
	responseData.def( py::init<std::string, unsigned int, int, int>() )
	.def( py::init<>() )
	.def( py::init([] (const py::buffer & b) {
			       py::buffer_info info = b.request();
			       std::cout << "###info format" << info.format;
			       if ( info.format != py::format_descriptor<unsigned char>::format() || info.ndim != 1 )
			       {
				       throw std::runtime_error( "Incompatible buffer format!" );
			       }
/*                auto l = info.shape[0]; */

			       auto *v = new ResponseData( info.shape[0] );
			       memcpy( v->data, info.ptr, info.shape[0] );
			       return(v);
		       } ) )
	.def( "setData", [] (ResponseData & r, const py::buffer & b) {
		      py::buffer_info info = b.request();
		      std::cout << "###info format" << info.format;
		      if ( info.format != py::format_descriptor<unsigned char>::format() || info.ndim != 1 )
		      {
			      throw std::runtime_error( "Incompatible buffer format!" );
		      }
		      if ( r.data == nullptr )
		      {
			      void* p = malloc( info.shape[0] );
			      if ( p == nullptr )
			      {
				      throw std::runtime_error( "Can't Allocate memory!" );
			      }
			      r.data = p;
		      }
		      r.len = info.shape[0];
		      memcpy( r.data, info.ptr, info.shape[0] );
	      } )
	/* / Bare bones interface */
	.def( "setDataType",
	      [] (ResponseData & r, int i) {
		      r.type = i;
	      } )
	/* / Provide buffer access */
	.def_buffer([] (ResponseData & r)->py::buffer_info {
			    return(py::buffer_info(
					   r.data,                                              /* Pointer to buffer */
					   sizeof(unsigned char),                               /* Size of one scalar */
					   py::format_descriptor<unsigned char>::format(),      /* Python struct-style format descriptor */
					   1,                                                   /* Number of dimensions */
					   { size_t( r.len ) },                                 /* Buffer dimensions */
					   {            /* Strides (in bytes) for each index */
					     sizeof(unsigned char) }
					   ) );
		    } )
	.def_readwrite( "key", &ResponseData::key, py::return_value_policy::automatic_reference )
	.def_readwrite( "data", &ResponseData::data, py::return_value_policy::automatic_reference )
	.def_readwrite( "status", &ResponseData::status, py::return_value_policy::automatic_reference )
	.def_readwrite( "len", &ResponseData::len, py::return_value_policy::automatic_reference )
	.def_readwrite( "type", &ResponseData::type, py::return_value_policy::automatic_reference );
}


class Wrapper
{
public:
	Wrapper()
	{
		py::gil_scoped_acquire acquire;
		_obj	= py::module::import( "main" ).attr( "PythonClass" ) ();
		_get_x	= _obj.attr( "get_x" );
		_set_x	= _obj.attr( "set_x" );
	}


	~Wrapper()
	{
		_get_x.release();
		_set_x.release();
	}


	int get_x()
	{
		py::gil_scoped_acquire acquire;
		return(_get_x().cast<int>() );
	}


	void set_x( int x )
	{
		py::gil_scoped_acquire acquire;
		_set_x( x );
	}


private:
	py::object	_obj;
	py::object	_get_x;
	py::object	_set_x;
};


void thread_func( int iteration )
{
	Wrapper w;

	for ( int i = 0; i < 1; i++ )
	{
		w.set_x( i );
		std::stringstream msg;
		msg << "iteration: " << iteration << " thread: " << std::this_thread::get_id() << " w.get_x(): " << w.get_x() << std::endl;
		std::cout << msg.str();
/*    std::this_thread::sleep_for(100ms); */
	}
}


int main()
{
	py::scoped_interpreter	python;
	py::gil_scoped_release	release; /* add this to release the GIL */

	std::vector<std::thread> threads;

	for ( int i = 0; i < 1; ++i )
		threads.push_back( std::thread( thread_func, 1 ) );

	for ( auto & t : threads )
		t.join();

	return(0);
}



