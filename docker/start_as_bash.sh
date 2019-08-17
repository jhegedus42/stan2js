echo $1
docker run -p 9000:8888 -e GRANT_SUDO=yes -v /tmp:/tmp_of_host --user root -it --name docker_playaround_$1 jhegedus42/docker-playaround:$1  bash

