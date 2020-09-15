# Docker

Delete All Untagged Images:

docker rmi $(docker images | grep "<none>" | awk '{print $3}')

Delere All container:

docker ps -q -a | xargs docker rm

sudo systemctl stop docker
sudo systemctl start docker
sudo systemctl stop containerd
sudo systemctl start containerd

Clean cache:
docker builder prune

Cleanup:
docker kill $(docker ps -q)
docker rm $(docker ps --filter=status=exited --filter=status=created -q)
docker rmi $(docker images -a -q)


# busybox

https://hub.docker.com/_/busybox

docker pull busybox

Shell:

docker run -it --rm busybox

@ scratch

Binary:

Dockerfile:
FROM scratch
COPY ./speedtest /speedtest
CMD ["/speedtest"]

docker build --tag speedtest:latest .

docker run -it speedtest

