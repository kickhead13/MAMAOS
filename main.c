#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char FIRST_BOOT = 0;//if 0 then do confi boot if not do normal boot
char *INFO_PATH = "Variables/info.txt"; //path to info.txt


//these next variables are simply global
//they are not part of info.txt and shouldn't be changed anywhere else other than this code
char *USER_COMMAND_PATH = "";


//#define ADMIN_TEXT_COLOR "red"

//(admin) username @ C > set --FIRST_BOOT 1



//Always execute this
//READS THE ENVIORENMENT VARIABLES
void ALWAYS_RUN_ON_BOOT();

//when the user first opens the OS
//cere : username, admin password, login password,
//cream FOLDERELE LA CARE ARE ACCES USERUL
void on_first_boot();

//read from Variables/info.text
char *read_info(int);

//automatically partitions OS
void auto_partition();

//START OF COMMANDS

//create a text file
int add_text_file(char*);

//creates directory in current directory
int add_dir(char*);

//delete directory if not in m@rius directory
void del_dir(char*);

//renames directory if not in m@rius directory
void rename_dir(char*);

//puts a string at the end of info.txt
void appends_to(char*,char*);

//clear screen
void clear_screen();

//access a directory
void access(char*);

//END OF COMMANDS

//m@rius main
void marius_main();

//m@rius command handler
void marius_handle(char *);

//m@rius neofetch
void neofetch();

//chess


//move piece on chess board
void move_chess_piece(char table[8][8],unsigned int);

//check if there is an element in char matrix
int is_in_matrix(size_t, size_t, char (*table)[], char);


//endd of chess


//################################################
int main() {
    //ALWAYS_RUN_ON_BOOT();
    add_dir("Variables");
    add_text_file("Variables/info.txt");
    add_text_file("Variables/ENVIORENMENT.txt");
	if(FIRST_BOOT == 0) on_first_boot();
}
//###############################################

int add_text_file(char name[]) {
    //strcat(name, ".txt");
    FILE *filepointer = fopen(name, "a");
    fclose(filepointer);
    printf("(m@rius) created \"%s\" file.\n", name);
}

void neofetch() {

    char *table[] = {
        "                           ",
        "     m1c\\ /&#@   %?$&#%!+@          username: %s ",
        "     ?:+!V^$?/   ?:+!^\\$?/          (m@rius) version: v0.0.1",
        "     *)/ V \\$1   *^/   \\\1           (m@rius) status: happy",
        "     U#|   &@5   U#|*@#&@5          MAMA version: v0.0.1",
        "     #%/   |:)   #%!   *$5          since: 14/03/2023",
        "                                    time: 1:50pm",
        "     %@$\\ /&#@   %?$&#%!+@  ",
        "     ?:+!%^$?/   ?:+!^\\$?/          CPU: %s",
        "     *)/ V \\$1   *^/   \\$1          GPU: %s",
        "     U#|   &@5   U#|*@#&@5  ",
        "     #%!   *:<   #%!   *$5  ",
        "                          ",
        "      (#@)_$*    /$|#\"@;:.  ",
        "     ?#3!/$5%4   #8%  a:<\\    ",
        "     !%4   &>#   \\#$6\\._     ",
        "     ):f.,_@:#   ,.,  a#P)   ",
        "     \\*#)E><3/   \\a3#5aNa/ ",
        "                              "

    };
    int i = 0;
    for(i = 0; i<19; i++)
        printf("%s\n", table[i]);
}

void clear_screen() {
    system("cls");
}

int is_in_matrix(size_t size_n_of_matrix, size_t size_m_of_matrix, char (*table)[size_m_of_matrix], char elem) {
    //printf("is in... ");
    int temp = size_m_of_matrix;
    for(;size_n_of_matrix-->0;) {
        size_m_of_matrix = temp;
        for(;size_m_of_matrix-->0;) {
            //printf("<%c, %d> ", table[size_n_of_matrix][size_m_of_matrix], size_m_of_matrix);
            if(table[size_n_of_matrix][size_m_of_matrix] == elem)
                return 1;
        }
        //printf("\n");
    }
    return 0;
}

void move_chess_piece(char table[8][8], unsigned int move) {
    table[(move/10)%10][move%10] = table[move/1000][(move/100)%10];
    table[move/1000][(move/100)%10] = ' ';

    //char temp = table[move/1000][(move/100)%10];
    //table[move/1000][(move/100)%10] = table[(move/10)%10][move%10];
    //table[(move/10)%10][move%10] = temp;

}

void access(char *dirname) {

    printf("%s", USER_COMMAND_PATH);

    //if the user is in default m@rius directory we have ""
    if(strcmp(USER_COMMAND_PATH, "") == 0) {
        USER_COMMAND_PATH = (char*)malloc(strlen(dirname)*10*sizeof(char));
        strcpy(USER_COMMAND_PATH, dirname);
        //printf("%s", USER_COMMAND_PATH);
        strcat(USER_COMMAND_PATH, "/");
        return;
    }

    //if we're not in m@rius directory
    if(USER_COMMAND_PATH[strlen(USER_COMMAND_PATH)-1] != '/')
        strcat(USER_COMMAND_PATH, "/");
    strcat(USER_COMMAND_PATH, dirname);
    strcat(USER_COMMAND_PATH, "/");
    return;

}

int add_dir(char *dirname) {
    char *TEMP = (char*)malloc(strlen(dirname) + strlen(USER_COMMAND_PATH) + 1);
    if(strcmp(USER_COMMAND_PATH, "")) {
        strcpy(TEMP, USER_COMMAND_PATH);
        strcat(USER_COMMAND_PATH, dirname);
        strcpy(dirname, USER_COMMAND_PATH);
        strcpy(USER_COMMAND_PATH, TEMP);
    }
    int i = mkdir(dirname,  0777);
    if(i != 0) {printf("(m@rius) couldn't create %s directory... retry.\n", dirname);
    return i;}
    printf("(m@rius) created \"%s\" directory.\n", dirname);
}

void chess() {
        printf("(m@rius) good luck and have fun!\n");
        char table[8][8] =
        {
            'T', 'N', 'B', 'Q', 'K', 'B', 'N', 'T',
            'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
            't', 'n', 'b', 'q', 'k', 'b', 'n', 't',
        };
        char disp_table[30][30];
        //DISPLAYING THE PIECES
         for(int i = 0; i<=8*3; i++) {
            for(int j = 0; j<=8*3; j++){
                disp_table[i][j] = ' ';
            }
        }

        unsigned int move;
        int model = 3, icont = 2, linecheck = 1;
        char move_counter = 1, line_contor = 0;
        while(is_in_matrix(8,8,table,'k') && is_in_matrix(8,8,table, 'K')) {
            //printf("%d", is_in_matrix(8,8,table,'k') && is_in_matrix(8,8,table, 'K'));
            //printf("it is");
            model = 3, icont = 2, linecheck = 1;
            for(int i = 0; i<8*3; i++) {
                if(linecheck == 1)model = 3;
                if(linecheck == -1) model = 0;

                if(icont == 0) {linecheck*=-1;icont = 3;};
                icont--;

                for(int j = 0; j<8*3; j++){
                    if(model == 3) {
                        while(model) {
                            model--;
                            disp_table[i][j]=177;
                            j++;
                        }
                    }
                    //if(j>=0 && j<3)disp_table[i][j] = "*";
                    model ++;
                }
            }

            for(int i = 1; i<8*3; i+=3) {
                for(int j = 1; j<8*3; j+=3){
                    disp_table[i][j] = table[i/3][j/3];
                }
            }
            printf("Move: %d\n", move_counter++);
            for(int i = 0; i<8*3; i++) {
                if((i-1) % 3 == 0) printf(" %d ", line_contor++);
                else printf("   ");
                for(int j = 0; j<8*3; j++){
                    printf("%c", disp_table[i][j]);
                }
                printf("\n");
            }
            printf("    0  1  2  3  4  5  6  7 \n");

            printf("[chess](m@rius) > ");
            scanf("%d", &move);
            move_chess_piece(table, move);
            line_contor = 0;
    }
    if(!is_in_matrix(8,8,table,'k')) {
        printf("UPPER-CASES WON!\n");
        return;
    }
    printf("LOWER-CASES WON!!\n");
}

void auto_partition() {
    printf("\n(m@rius) auto-partitioning...\n");

    add_dir("C");
    add_dir("D");
    add_dir("C/Desktop");

    char s[100];
    printf("[done: please \"reboot\"](m@rius) > ");
    scanf("%s", s);
    marius_handle(s);
}

void marius_handle(char *command) {

    if( strcmp(command, "cls") == 0 || strcmp(command, "clear") == 0)
        {clear_screen();return;} //clear terminal screen

    if(strcmp(command, "chess") == 0) {
        chess();
        return;
    }

    if( strcmp(command, "neofetch") == 0 )
        neofetch();

    if( strcmp(command, "done..") == 0 )
        exit(0);

    if( strncmp(command, "mke-dir ", 7) == 0) {
        add_dir(command+8);
        return;
    }

    if(strncmp(command, "access", 6) == 0) {
        access(command+7);
        return;
    }

}

void marius_main() {
    char s[100];
    while(1) {
        printf("[setup](m@rius) %s > ", USER_COMMAND_PATH);
        fflush(stdin);
        scanf("%[^\n]s", s);
        marius_handle(s);
        strcpy(s, "");
    }
}


void appends_to(char *filename, char *text_to_append) {
    FILE *filepointer = fopen(filename, "a");
    fprintf(filepointer, "%s\n", text_to_append);
    fclose(filepointer);
}

void on_first_boot() {
    char username[100], passwd[100], adminpasswd[100], len = 0, yesno;
    //system("cls");
    printf("############################################# WELCOME TO MAMA OS #############################################\n\n");
    printf("This is an open-source faux-O.S., developed by Ana Alexandru (alexandru.ana03@e-uvt.ro) and Duna Alexandru ().\n");
    printf("You will need to configure your O.S. (create an (user) account, \"partition\" disk, etc.)\n");
    printf("\n(m@rius) Do you want help configuring your O.S.?\n");
    printf("(m@rius) (Y/n) > ");
    scanf("%c", &yesno);

    if(yesno == 'n' || yesno == 'N') marius_main();

    printf("(m@rius) give me a username for (user) > ");
    scanf("%s", username);
    printf("(m@rius) give us a password for this (user) > ");
    scanf("%s", passwd);
    while(0) {
        printf("(m@rius) your password was too short, give me a longer password > ");
        scanf("%s", passwd);
    }
    printf("(m@rius) do you want to set a different password for (admin) (Y/n) > ");
    fflush( stdin );
    scanf("%c", &yesno);
    if(yesno == 'n' || yesno == 'N') strcpy(adminpasswd, passwd); //the admin has the same password as the user
    else { //the admin needs a different password
        printf("(m@rius) give me a strong admin password > ");
        scanf("%s", adminpasswd);

        char strength_meter = 0;

        while(0) {
            switch(strength_meter) {
                case 0: printf("(m@rius) the admin password needs to be stronger > ");break;
                case 1: printf("(m@rius) the admin password needs to be even stronger > ");break;
                case 2: printf("(m@rius) even stronger!! > ");break;
                default: printf("(m@rius) EVEN STRONGER!!!! > ");break;
            }
            scanf("%s", passwd);
            strength_meter++;
        }
    }

    //system("cls");
    printf("\nPARTITIONING MAMA OS...\n\n");
    printf("(m@rius) do you want to manually partition (Y/n)? > ");
    fflush( stdin );
    scanf("%c", &yesno);

    //puts user/admin info in info.txt
    appends_to(INFO_PATH, username);
    appends_to(INFO_PATH, passwd);
    appends_to(INFO_PATH, adminpasswd);


    if(yesno == 'Y' || yesno == 'y') {
        marius_main();
    }

    else auto_partition();



}


