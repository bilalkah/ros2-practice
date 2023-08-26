xhost +local:root &> /dev/null
docker run \
	-it --rm\
	--privileged \
	--net=host \
	--gpus all \
	--env=NVIDIA_VISIBLE_DEVICES=all \
	--env=NVIDIA_DRIVER_CAPABILITIES=all \
	--env=DISPLAY \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
	-v /home/bilal/dockers/ros2-humble/ros2_ws/src:/ros2_ws/src \
	--name ros2_humble \
	humble:latest \
	/bin/bash
