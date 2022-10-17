#include "pybind11/embed.h"
#include "pybind11/stl.h"
namespace py = pybind11;
using namespace std::chrono_literals;

class ResponseData {
public:
	ResponseData(std::string r_key, unsigned int r_len, int r_status ,int r_type ): key(r_key), len(r_len), type(r_type), status(r_status){

	};
        ResponseData( size_t r_len){
            len =      static_cast<unsigned int>(r_len);
	   data = malloc(r_len);
	};
        ResponseData(){
	};
    std::string key;
     void* data;
    unsigned int len;
    int status;
    int type;
};
