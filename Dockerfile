# This is an auto generated Dockerfile for ros:desktop-full
# generated from docker_images_ros2/create_ros_image.Dockerfile.em
FROM osrf/ros:humble-desktop-jammy

RUN apt install -y --no-install-recommends \
    software-properties-common \
    add-apt-repository universe \
    curl \
    sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg \
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# install ros2 packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-humble-desktop-full=0.10.0-1* \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-dev-tools \
    wget \
    git \
    build-essential \
    tmux \ 
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    ~nros-humble-rqt* \
    ros-humble-ros2bag \
    ros-humble-rosbag2-storage-default-plugins \ 
    python3-colcon-common-extensions \
    ros-humble-pluginlib \
    nano \
    && rm -rf /var/lib/apt/lists/*

RUN echo "source /opt/ros/humble/setup.bash" >> /root/.bashrc \
    && echo "source /ros2_ws/install/setup.bash" >> /root/.bashrc \
    && echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> /root/.bashrc \
    && echo "export _colcon_cd_root=/opt/ros/humble/" >> /root/.bashrc \
    && echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> /root/.bashrc \
    && echo "alias cb='colcon build --symlink-install'" >> /root/.bashrc \
    && echo "alias resolve='rosdep install -i --from-path src --rosdistro humble -y'" >> /root/.bashrc \
    && echo "alias cb_one='colcon build --symlink-install --packages-up-to'" >> /root/.bashrc \