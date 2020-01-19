/*
 * File:   def.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 6 października 2017, 11:47
 */

#ifndef pjpl_DEF_H
#define pjpl_DEF_H

#include <string>
#include <map>
#include <vector>

namespace pjpl {

typedef std::size_t AutoId;
typedef std::vector<std::string> StrV;
typedef std::vector<std::wstring> WStrV;

// key : param name
// val : current param value
typedef std::map<std::wstring, std::wstring> ParamsMap;

// key : param name
// val : list of valid values
typedef std::map<std::wstring, WStrV > InParamsMap;

typedef int StatusCode; // if < 0 then error if > 0 then ok if = 0 unknown/not set

// from zmc_intrusion_trace/intrusion-service-lib/include/plate-def.h
typedef enum RecognitionEnum {
    BAD_STRING = -1,    // string not a plate and not a face
    UNKNOWN = 0,        // string is a plate but not assigned to black or white list
    WHITE = 1,
    BLACK = 2
} RecognitionType;

}


#endif /* pjpl_DEF_H */

