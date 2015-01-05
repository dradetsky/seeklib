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
    def get_data
      [
        self[:sig1].to_a,
        self[:sig2].to_a,
        self[:sig3].to_a,
        self[:avgl].to_a
      ]
    end
    def inspect
      data = get_data.map {|x| x.inspect}
      "#<Sig: #{data.join ' '}>"
    end
    # these methods might not be fast enough, but whatever
    def marshal_dump
      Marshal.dump get_data
    end
    def marshal_load str
      array = Marshal.load str
      fields = [:sig1, :sig2, :sig3, :avgl]
      fields.zip(array).each do |field, data|
        data.each_index do |i|
          self[field][i] = data[i]
        end
      end
    end
  end

  attach_function :calcDiff, [:pointer, :pointer], :double
  attach_function :pathSig, [:string], :pointer

  def self.path_sig path
    Sig.new pathSig(path)
  end
end
