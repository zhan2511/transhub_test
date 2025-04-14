#####CAN'T WORK#####
#####YOU NEED TO COPY THE COMMAND MANUALLY#####

sudo docker start transhub

sudo docker exec -it transhub /bin/bash


#####YOU NEED TO COPY THE COMMAND STEP BY STEP#####

cd /home/none_root/transhub/cc-training/

./autogen.sh && ./configure && make

sysctl -w net.ipv4.ip_forward=1

cd /home/none_root/transhub/cc-training/datagrump/

su none_root -c "./run-contest controller.cc"

mm-throughput-graph 500 ./contest_uplink_log > a.svg

exit

#####WHEN FINISH CODING, TRY TO RESTART CONTAINER#####

sudo docker restart transhub




