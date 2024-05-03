#!/bin/bash
cmake -B build
cmake --build build
cd build
echo "#!/bin/bash
     cd ..
     cmake --build build" >run.sh
chmod +x run.sh
cp ./../BE* .
