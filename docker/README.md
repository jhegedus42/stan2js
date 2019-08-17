
#This is a description on how I use docker to develop this repo.


About the docker image itself:

I simply used a standard Ubuntu docker image as a start 
to create my custom version of it: I installed some of 
my favorite tools, like `tmux` and `mc`, and all the 
things that were needed for this git repo to work, 
for example `node.js` and `python`, and the compilers, 
for example `em++` or `clang` and whatever environment 
variables were needed to be set.

I cannot make the image itself public because it contains
sensitive information (ssh-keys, and other private stuff,
I am using this image for all sorts of other stuff as well,
which I don't want to make public).


The image itself is stored in docker hub, in a private 
repo. This means, if you try to pull it, it won't work.

However, the workflow described here can be used with pretty
much any standard ubuntu based image which you can find
on Docker Hub, then you can customize the image to your
own liking, whatever that may be. 


Ok, here it comes, an example workflow.

---
Let's assume that the highest number tag in this example is 0012, 
that is:

```
./print_docker_images.sh
```

prints the following:
```
./print_docker_images.sh
name :   jhegedus42/docker-playaround        tag :   0012
name :   jhegedus42/docker-playaround        tag :   0011
name :   jhegedus42/docker-playaround        tag :   0010
```

---
Then we can start the docker image by:

./start_as_bash.sh 0012

- We land in a bash shell.
- Then we start `tmux`. 
- Then we do some changes to the container's file system.
- We exit all panes in `tmux` by typing `exit`.
- Finally exit docker by exiting the main bash process by typing
"exit".


---
Then we list the docker containers by
```
docker ps -a
```
we see that the name if the container to be commited is `docker_playaround_0012`.

---
Then we commit the most recent state of the docker image by:
```
docker commit -m 'cmd stan compiled - using em++' docker_playaround_0012 jhegedus42/docker-playaround:0013
```


---
Then we remove the docker container:

```
docker rm -r docker_playaround_0012
```

---
Then we push the docker image by:
```
docker push jhegedus42/docker-playaround:0013
```

which will print something like:

```
Jozsefs-MBP:~ joco$ docker push jhegedus42/docker-playaround:0013
The push refers to repository [docker.io/jhegedus42/docker-playaround]
bef5a20c3e67: Preparing
3d460619a983: Preparing
f8912a5bebfd: Preparing
0cf231a24ff9: Preparing
1090ca9938ae: Preparing
393896029ebd: Preparing
9362b2f68584: Preparing
c31043a35b90: Preparing
12961b78d057: Preparing
e798056d0114: Preparing
64d3d89754f8: Preparing
a1fdba0f1e58: Preparing
bef5a20c3e67: Pushing [=================================>                 ]  169.5MB/251.1MB
c0c4e0f3d3af: Layer already exists
c172d93bea18: Layer already exists
83c7fc31ccef: Layer already exists
.
.
.
02e0f4b07615: Layer already exists
75e70aa52609: Layer already exists
dda151859818: Layer already exists
fbd2732ad777: Layer already exists
ba9de9d8475e: Layer already exists
0013: digest: sha256:f6a2d873c77eb72cfa02407d76e2d45697688fc625da69ab166199c8c9a19653 size: 8519
```


---

Then we can run:

```
Jozsefs-MBP:all-spark-notebook joco$ ./print_docker_images.sh
name :   jhegedus42/docker-playaround        tag :   0013
name :   jhegedus42/docker-playaround        tag :   0012
name :   jhegedus42/docker-playaround        tag :   0011
name :   jhegedus42/docker-playaround        tag :   0010
```

and see that our latest image in the local repo has a tag of `0013`.

---

Tip:

If you close the window of a terminal in which a docker process is running,
for example `mc` or `mux` then later you can use the `docker attach` command
to "re attach to it`, like this :
```
docker attach docker_playaround_0012
```

