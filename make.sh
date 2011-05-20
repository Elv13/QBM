if [ "$USER" != "root" ]; then
  echo You need to be root
  exit
fi

gcc main.c -o qbm
if [ $? -ne 0 ]; then
  echo Compilation failed aborting
  exit
fi

chmod 700 qbm
cp qbm /sbin/
cp scripts/* /sbin/

echo Finished
echo
echo Now make qbm your init system using grub or any other way you like
