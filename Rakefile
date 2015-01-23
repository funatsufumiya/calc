task :all => [:js, :c]

task :js do
  sh "kmyacc calc.jsy"
end

task :c do
  sh "kmyacc calc.y"
  sh "mv y.tab.c calc.c"
  sh "gcc -O3 calc.c -o calc"
end