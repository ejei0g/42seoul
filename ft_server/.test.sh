docker build -t test .
docker run -e AUTO_INDEX=0 -it --rm -p 80:80 -p 443:443 test
