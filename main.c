/**
 * QBM (Quick Boot Manager) is an oversimplified init and DM system for Linux
 * It allow to boot to the desktop in less than 1 second by hardcoding and 
 * parallelizing much of the process. Edit the variable bellow and the various 
 * scripts to fit your hardware and your needs.
 * @author Emmanuel Lepage Vallee (Elv13) <elv1313@gmail.com>
 * 
 *          ---THE DEFAULT VERSION WILL NOT WORK FOR YOU---
 *                KEEP A FALLBACK SYSTEM AT ALL TIME
 *
 * Distributed under the BSD license, no warrenty what so ever, be warned
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Script path
#define CRITICAL       "dash /sbin/critical.sh"    //Critical services to start X
#define BOOT_READAHEAD "dash /sbin/readahead1.sh"  //File used during boot
#define STARTX         "/sbin/startx.sh"      //Script used to startx X
#define DE_READAHEAD   "dash /sbin/readahead2.sh"  //Common binaries and libraries
#define POST_PHASE1    "dash /sbin/post1.sh"       //Services to startx after X
#define POST_PHASE2    "dash /sbin/post2.sh"       //Services depending on post1
#define BLOAT          "dash /sbin/bloat.sh"       //Other services (less than necessary)

int main() {
  //Boot the necessary services to start X
  system(BOOT_READAHEAD);
  system(CRITICAL);

  //Slit the process in two thread
  pid_t cpid; 
  cpid = fork();

  if (cpid == 0) { //Time to start X
    //Check in /etc/passwd to get the right values
    setuid(1000);
    setgid(1005);

    //Set to your home directory
    char pwd[]     = "/home/lepagee";
    chdir(pwd);

    //Use "printenv" to know the value of these variables, you may want to add more
    char home[]    = "HOME=/home/lepagee";
    char user[]    = "USERl=lepagee";
    char lang[]    = "LANG=en_US.UTF-8";
    char shell[]   = "SHELL=/bin/bash";
    char term[]    = "TERM=/usr/bin/urxvt";
    char editor[]  = "EDITOR=nano";
    char logname[] = "LOGNAME=lepagee";

    //Do not edit
    char* envVar[] = {home,user,lang,shell,term,editor,logname, NULL};
    char* args[] = { pwd, STARTX, NULL };
    execve("/bin/dash",args,envVar); //Yes, you do need dash, bash/zsh are too slow
  }
  else { //Finish the boot process
    sleep(2);//TODO use a real lockfile
    system(DE_READAHEAD);
    system(POST_PHASE1);
    system(POST_PHASE2);
    system(BLOAT);
  }
}
