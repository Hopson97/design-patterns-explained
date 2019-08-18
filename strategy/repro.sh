docker run -it ubuntu
cd
apt update
apt install git cmake build-essential libsfml-dev --assume-yes # 600 MB download
git clone https://github.com/Hopson97/design-patterns-explained.git
cd design-patterns-explained/strategy/
chmod 764 scripts/*.sh # we should probably make a PR to fix these files permissions
./scripts/build.sh

