require 'rake/clean'

CLEAN.include('*.o')
CLOBBER.include('*.bin')

source_files = Rake::FileList["*.c"]
object_files = source_files.ext(".o")
gcc_params = "-lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lpthread -lm -ldl"
gcc_flags = "-lpthread"
desc "Build the binary executable"
task :binary => object_files do
  sh "g++ #{gcc_flags} #{object_files} -o app.bin #{gcc_params}"
end

rule '.o' => '.c' do |task|
  sh "g++ #{gcc_flags} -c #{task.source} #{gcc_params}"
end

# rule '.o' => '.cpp' do |task|
#   sh "g++ #{gcc_params} -c #{task.source}"
# end

desc "rake binary"
task :default => :binary
