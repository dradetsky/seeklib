require 'ffi'

$libseek_path = File.join File.dirname(__FILE__), 'libseek.so'

module LibSeek
  extend FFI::Library
  ffi_lib $libseek_path

  class Sig < FFI::Struct
    layout \
    :sig1, [:int, 40],
    :sig2, [:int, 40],
    :sig3, [:int, 40],
    :avgl, [:double, 3],
    :height, :int,
    :width, :int
  end

  attach_function :calcDiff, [:pointer, :pointer], :double
  attach_function :pathSig, [:string], :pointer
end
