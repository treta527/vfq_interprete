cmake_minimum_required(VERSION 3.4.1)  # for example

add_library( verifiquese

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ../ios/Classes/verifiquese.cpp ../ios/Classes/convert.cpp ../ios/Classes/lll.cpp ../ios/Classes/document.cpp ../ios/Classes/base64.cpp ../ios/Classes/persona.cpp ../ios/Classes/utilities.cpp)
