extension1=".toleblists"
extension2=".tileblasts"
for folder in ../tiles/*; do for file in $folder/*.tilewalls; do 
    echo running on $file
    time timeout 60 ./tileblaster $file; done; done
