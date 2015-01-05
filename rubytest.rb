require './bind'

def check_marshal
  sig = LibSeek::path_sig('../../index/.imgs/1/00009.bmp')
  File.open '.dump', 'w' do |f| f.write Marshal.dump(sig) end
  puts sig.inspect
end

def check_load
  sig = Marshal.load(File.open('.dump').read)
  puts sig.inspect
end

def check_diff
  sig0 = LibSeek::path_sig('../../index/.imgs/1/00009.bmp')
  sig1 = LibSeek::path_sig('../../index/.imgs/1/00010.bmp')
  d = LibSeek::calcDiff sig0, sig1
  puts d
end

def check_load_diff
  sig0 = Marshal.load(File.open('.dump').read)
  sig1 = LibSeek::path_sig('../../index/.imgs/1/00010.bmp')
  d = LibSeek::calcDiff sig0, sig1
  puts d
end

if ARGV.size == 0
  check_marshal
else
  check_load_diff
end
