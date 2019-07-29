sudo apt-get install build-essential

sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev guile-1.8 \
guile-1.8-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev \
libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev \
libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev \
libslang2-dev libasound2 libasound2-dev

wget http://download.savannah.gnu.org/releases/libgraph/libgraph-1.0.2.tar.gz
tar xfvz libgraph-1.0.2.tar.gz
rm libgraph-1.0.2.tar.gz

cd libgraph-1.0.2
./configure
make
sudo make install
sudo cp /usr/local/lib/libgraph.* /usr/lib
rm libgraph-1.0.2

# Test if all works fine
cd ..
g++ test_graphics.cpp -lgraph
./a.out 
