/************* cd_ls_pwd.c file **************/
int cd()
{
  printf("cd: under construction READ textbook!!!!\n");

  // READ Chapter 11.7.3 HOW TO chdir
}

int ls_file(MINODE *mip, char *name)
{
  printf("ls_file: to be done: READ textbook!!!!\n");

  char *t1 = "xwrxwrxwr-------";
  char *t2 = "----------------";

  char ftime[64];

  // READ Chapter 11.7.3 HOW TO ls
  INODE* lsPrinter = &mip->INODE;

  if ((lsPrinter->i_mode & 0xF000) == 0x8000) // if (S_ISREG())
    printf("%c",'-');
  if ((lsPrinter->i_mode & 0xF000) == 0x4000) // if (S_ISDIR())
    printf("%c",'d');
  if ((lsPrinter->i_mode & 0xF000) == 0xA000) // if (S_ISLNK())
    printf("%c",'l');
  for (int i=8; i >= 0; i--){
    if (lsPrinter->i_mode & (1 << i)) // print r|w|x
      printf("%c", t1[i]);
    else
      printf("%c", t2[i]); // or print -
  }
  printf("%4d ",lsPrinter->i_links_count); // link count
  printf("%4d ",lsPrinter->i_gid); // gid
  printf("%4d ",lsPrinter->i_uid); // uid
  printf("%8d ",lsPrinter->i_size); // file size
  // print time 
  strcpy(ftime, ctime(&lsPrinter->i_ctime)); // print time in calendar form
  ftime[strlen(ftime)-1] = 0; // kill \n at end
  printf("%s ",ftime);
  // print name
  printf("%s", basename(name)); // print file basename
  // print -> linkname if symbolic file
  if ((lsPrinter->i_mode & 0xF000)== 0xA000){
    readlink("./", ftime, 64);// use readlink() to read linkname
    printf(" -> %s", ftime); // print linked name
  }
  return 0;
}

int ls_dir(MINODE *mip)
{
  printf("ls_dir: list CWD's file names; YOU FINISH IT as ls -l\n");

  char buf[BLKSIZE], temp[256];
  DIR *dp;
  char *cp;

  get_block(dev, mip->INODE.i_block[0], buf);
  dp = (DIR *)buf;
  cp = buf;
  
  while (cp < buf + BLKSIZE){
    strncpy(temp, dp->name, dp->name_len);
    temp[dp->name_len] = 0;
  
    //ls_file(dp->inode, dp->name);
    //printf("%s  ", temp);
    printf("dir len = %c\n", dp->file_type);
    cp += dp->rec_len;
    dp = (DIR *)cp;
  }
  printf("\n");
}

int ls()
{
  printf("ls: list CWD only! YOU FINISH IT for ls pathname\n");
  ls_dir(running->cwd);
}

char *pwd(MINODE *wd)
{
  printf("pwd: READ HOW TO pwd in textbook!!!!\n");
  if (wd == root){
    printf("/\n");
    return;
  }
}



