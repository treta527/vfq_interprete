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

    String output = Utf8.fromUtf8(_parse(Utf8.toUtf8(l.toString()),
        Utf8.toUtf8(rawData), Utf8.toUtf8(usuario), Utf8.toUtf8(licencia)));

    return output;
  } catch (e) {
    print("ERROR: $e");
    return e.toString();
  }
}
