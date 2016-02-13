#!/bin/bash

APP_NAME=agent
DIST_TAR_NAME=agent.tgz
WORK_PATH=`pwd`
TMPDIR=$WORK_PATH/mytmp
BASE_PATH=/usr/local/sa/agent
NAKED_SH=$TMPDIR/install-nk.sh
INSTALL_LOG=$BASE_PATH/install.log
CRON_FILE_TMP_1=/tmp/cron.tmp.1
CRON_FILE_TMP_2=/tmp/cron.tmp.2
STOP_AGENT=/usr/local/sa/agent/stop.sh
OLD_AGENT=/usr/local/secu/tconfscan
makedir ()
{
        if [ ! -d $1 ]; 
        then
                mkdir -p $1
        fi
}
untarfile()
{
        if [ ! -d $2 ]; 
        then
                mkdir -p $2
        fi
        if [ -f /bin/tar ];then
                tar xzfv $1 -C $2
        else
                ttars xzfv $1 -C $2
        fi
        if [ $? != 0 ];
        then
                echo "tar -xzvf $1 -C $2 ......[no],abort!" >> $INSTALL_LOG;
#               exit -1;
        fi
}
crontab -l -u root > $CRON_FILE_TMP_1
grep -Evw 'aide|secu-tcs-agent' $CRON_FILE_TMP_1 > $CRON_FILE_TMP_2
crontab $CRON_FILE_TMP_2 -u root
ps aux |grep secu-tcs-agent| grep grep -v |awk '{print $2}' > /tmp/sagent.pid
while read pid
do
        kill -9 ${pid}
done < /tmp/sagent.pid
if [ -d "$OLD_AGENT" ];then
        rm -rf /usr/local/secu/tconfscan 
fi
if [ -f "$STOP_AGENT" ];then
        bash $STOP_AGENT
fi
if [ ! -d $BASE_PATH ];
then
        makedir $BASE_PATH
        chmod 755 $BASE_PATH -R
        makedir $BASE_PATH/secubase
        makedir $BASE_PATH/plugins
fi
##############check unzip
FIND_UNZIP=`ls /usr/bin/unzip|wc -l`
if [ "$FIND_UNZIP" -eq "0" ]
then
        cp -r $WORK_PATH/unzip /usr/bin/unzip
        chmod +x /usr/bin/unzip
fi
echo "-------------------begin install-------------------" >> $INSTALL_LOG
echo "[extracting file] ......" >> $INSTALL_LOG
untarfile "$WORK_PATH/$DIST_TAR_NAME" $TMPDIR
chmod +x ${NAKED_SH}
${NAKED_SH}
echo "------------------------------------------------------------------------------" 
echo "[install succ] at time:[`date`]" 
echo "                   dir:[$BASE_PATH]"
echo "                  pack:[$DIST_TAR_NAME]"
echo "-------------------------------------------------------------------------------"
echo "[RESULT] sec-agent install OK"
