#pragma once
#pragma once

//
// NB: "extern C" to avoid procedure name mangling by C++ compiler
//

extern "C" _int64 g; // external global variable g

extern "C" _int64 _cdecl min(_int64, _int64, _int64);
extern "C" _int64 _cdecl p(_int64, _int64, _int64, _int64);
extern "C" _int64 _cdecl gcd(_int64, _int64);
extern "C" _int64 _cdecl q(_int64, _int64, _int64, _int64, _int64);