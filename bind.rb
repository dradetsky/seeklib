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
    :avgl, [:double, 3]
    def inspect
      data = [
        self[:sig1].to_a.inspect,
        self[:sig2].to_a.inspect,
        self[:sig3].to_a.inspect,
        self[:avgl].to_a.inspect
      ]
      "#<Sig: #{data.join ' '}>"
    end
  end

  attach_function :calcDiff, [:pointer, :pointer], :double
  attach_function :pathSig, [:string], :pointer

  def self.path_sig path
    Sig.new pathSig(path)
  end
end
