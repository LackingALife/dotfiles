extension1=".toleblists"
extension2=".tileblasts"
for folder in ../tiles/*; do for file in $folder/*.tilewalls; do 
    echo running on $file
    timeout 60 time ./tileblaster $file; done; done
