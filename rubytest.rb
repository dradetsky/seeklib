require './bind'

if ARGV.size == 0
  puts LibSeek::path_sig('../../index/.imgs/1/00009.bmp').inspect
else
  puts LibSeek::path_sig(ARGV.first).inspect
end
