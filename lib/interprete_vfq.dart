import 'dart:ffi'; // For FFI
import 'dart:io'; // For Platform.isX
import 'package:ffi/ffi.dart';
import 'dart:typed_data';
import 'dart:convert';

final DynamicLibrary verifiqueseLib = Platform.isAndroid
    ? DynamicLibrary.open("libverifiquese.so")
    : DynamicLibrary.process();

typedef parse_func = Pointer<Utf8> Function(Pointer<Utf8> f, Pointer<Utf8> arr,
    Pointer<Utf8> user, Pointer<Utf8> licencia);

String parse(String rawData, String usuario, String licencia) {
  try {
    final _parse = verifiqueseLib
        .lookup<NativeFunction<parse_func>>("convert")
        .asFunction<parse_func>();
    int l = rawData.length;
    //var bytes =ascii.encode(rawData);
   // var bytes =latin1.encode(rawData);
   var bytes = utf8.encode(rawData);
   print("Bytes::: $bytes");
   String _salida = base64.encode(bytes);
    //String _salida="STM3MDMwNTc4OO+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/vVB1YkRTS18x77+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+9ODUwNDQyNTUxMTQyNzIwNTQ477+977+9TUFDSEFET++/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/vUNBUlZBSkFM77+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+9RFlMQU7vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv71TQU5USUFHT++/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/vTBNMjAxMzAxMjIyNzA4MjBCLe+/ve+/vTICPe+/ve+/vRdQw7/CgMKAb8KPb359dH3CosKPZG7CmXHCqcKJwqlgwp9iwojCgcKvQMKgTsKkVcKFMMKEwqBaw4/Cg8OFYT1tw4TCmcKdXcKxwpfCs8KJwr7CoMOIa8KnwptIXcKDwoDCqMKNwp3Cm8KRT8KXwpttwo3Cm3nCpXhLwoLCoWbCq3XCvWDCrMKCw4Vow4bCksOBej1mXcKAwpbCkFZzYmnCilRyYMKSX8KTwqNtbnLCi8KGYsKNwqFpecKHwp5+wppzwpR8acKGMsOOKyVRwqrDvcOvX0Nsw6rCpMKQw7Lvv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv703AjLvv73vv71cTcO/woDCgHtvbMKNwoZuwo1twpTChcKGwpHCt8KPV8KNwrR9w450w5pbSsKOw4Z6QsKRwpthP3E3XMKRX1pPwoJNcmRqc37CmcKAwqLCl8KEwqB8wo7CnMKXcsKhwpLCqcKMwqvCgsKawqfCr3rDgWTDg3fDim/DgMKGw4LCmT3CgljCh1R4V2p5VO+/vWZsanBiZHJ6aXtscnHDhV/Ci8OSbmbDu8Kfwookw7J5wrHCssO+77+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+9IcOdw689w4gKXFp0w7bDnsKZD8Kew5RYMDNXwq8TaMO/LDA5w5bDqsOWwqB4woENwpBnwqwBEQEh";
    // String _salida = "MDIwNDI0OTA1MDEzQSAgICAgICAgIDAyMTA3NDE3ODI5MiAgICAgIDE2NDQxMjkwMTA5ODYxNjQ0N01BQ0hBRE8gICAgICAgICAgICAgICAgSkFJTUVTICAgICAgICAgICAgICAgICBMRU9OQVJETyAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgICAgME0xOTg2MDIyODA0MDAyNUFCKzLCkcK5wonCi3/CgsKnfsKSY8KBwpjCqsKWcsKQwonCosK3worCoFjCpMKjwpRTcVvChcKsdcKnbsKjf05jZHJTwr9hwqDCslrCim9OwpZEXMKcwqHCusODwqPDgMKtwpM8wp7DgFBqwqU8WVfCh8ODaURLwoHCqMOCSnnCpcOFw5p1SGnDlMKgw5nCl8OcbWzDg8OicMKmw47DjcK4PHvCoCrCgSlnMXgqw6PCnMOpwozDosKnw5DDgcOnXGnDuWDvv73vv71OwqXDqO+/ve+/vUEDw7/Cv2/DiG7DkBbCvMKSVsKtEMOibivDhMOEcMOPJMOSHwwzLT3Dt2VUw5TDk1M3wpHCucKMfm7ChW97e8KUwo50eWvClMKOZn95Z3BrfsKcZMKPeV5tYcKSwqRdwpfCgVjCjMKoXsKfalnCpmrCj1XCn13Cr8KMTsKHU2rChU/CmcKuSXfCpltIwoLCq2BtwrVLwpXCikrCt31IwpHCvMKMW0rCmMK/PMKCez5/w4XCoEV0w4Y8wpXCv2PCqkbCksOIwqTDgGg6NXHDhsKaOWE5wqM+wrDCkDBAP0AqBMOLD8Oww4YDw6wIAnI8wqQ6Lzlfwq7DksK0CxjDjsOrwr0OwqpDwpnDlsKew6rDkMKmwrZzwr9Ta17DtcKFUMKfwrPDlj/DmMKrKsKTWCrClsOuYkPClz7CiSFZw4HCjVsOwrxaTQjCuX7DkGoCwpt5WhvCuCE=";
    //String _salida =
        "MDM5MzE4NDMz77+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+9UHViRFNLXzHvv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv70zMzExODY0MTAwNzIzMDI0NDhBTlRFUVVFUkHvv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv73vv71NQVJUSU5FWu+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/vURBVklE77+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+977+9RVJORVNUT++/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/ve+/vTBNMTk3NzA1MDMwMzAwMTBBK++/ve+/vTICQ++/ve+/vXxbw7/CgMKAanDCi8KrccKSdGHCgFbCiE1zwqRuwphqwqjCiMK3wotfwpVZXcKYwpnCukfCpkrClDbCm1N9woR2LW/CuXbDkn3DkcKgw51uwrgrwr7ClMKxwq0xUsKxwpfCrsKgPDtCSsKswqnCqixlUcKPWMKvWDzClsKvZMKxUkLCicKkcsK1UMK4RsK9ZcKpdsKkw4nDh1jDiEPDkMKJWHPDlHPDmEzChcKFwqTCl1U3ZGrCicKQwpgwWk5sScKINmZewoBEwoM8dMKIwpjCtMKESsKSdcKdZCnCtsOfb0QtworDm0VEw73vv73vv703AkPvv73vv713WcO/woDCgMKBwpzCpcKywoN1wovCqsKXwrR0wpjCjcK2wpdibcKQdMKrwpdnwptYZsKawplxZsKlT8KpW8KSZcKEQcKQw4pywq56w4jCosOAwojDiMKTw4LCmcK6wppNa0RjXV/CrsKOe3/CpsKPfn3Cn8KdwpFewqVaYMOBacKzwqhUwrRuwrdWwrvCuMOFXMKuwoRVwovChsKERXVJWVxSworCicKTwonCqMKQYlx2wofCn8KReVPCj0dqbsKSwo9vZnhefsKPwoZTwpHCmcKUSHPCisKiwq5EwolSw4/CrMK0wpXDrMO6wpotw5d1EElBw77vv73vv73Cg8OJWMKcfsOPwrx9IcOdwpRME2JYw63CimXDkXUYFMKfw6XDkBbDnMO0w7dXw6fDuMKQwoJgwq3DpgVpwr4=";

   // final _ptr = Utf8.toUtf8(bytes.toString()).cast<Int32>();
    print("Contenido tamaño: $l");
    String output = Utf8.fromUtf8(_parse(Utf8.toUtf8(l.toString()),
        Utf8.toUtf8(rawData), Utf8.toUtf8(usuario), Utf8.toUtf8(licencia)));
    //print("Saliendo de método parce c++");
    //output = utf8.decode(base64.decode(output));
   // print("Salida :: $output");
    return output;
  } catch (e) {
    print("ERROR: $e");
    return e.toString();
  }
}
