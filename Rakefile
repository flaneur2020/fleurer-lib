OFiles = %w{fdict.o test.o}
CFlags = '-Wall'

task :run => [:link] do 
  sh "./test"
end

task :link => OFiles do
  sh "gcc #{CFlags} #{OFiles.join(' ')} -o test"
end

[
  ['src/fdict.c', 'src/fdict.h'],
  ['src/test.c']
].each do |fn_c, *_|
  fn_o = File.basename(fn_c).ext('o')
  file fn_o => [fn_c, *_] do
    sh "gcc #{CFlags} -c #{fn_c}"
  end
end
