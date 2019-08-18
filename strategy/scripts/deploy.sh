sh scripts/build.sh release 

rm -rf -d fake-paint

mkdir fake-paint

cp bin/release/fake-paint fake-paint
cp -r res fake-paint

echo "Deploy build created."
echo "cd fake-paint to find it"