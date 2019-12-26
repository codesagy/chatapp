// Name : Sagar Adhalge
// Assignment : Chat Application using UNIX System V IPC message queue.

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

// Macro Definitions
#define MAX_CHAR 512
#define BUFFER_SIZE 512

// MessageBody Definition
struct MessageBody
{
    char name[256] ;
    char body[256] ;
};

// Message Definition
struct Message
{
    long int messageType ;
    struct MessageBody messageBody ;
};

// Execution starts from here
int main()
{
    // Variable declaration and initialization
    char sender[25], receiver[25] ;
    char chatBuffer[BUFFER_SIZE] ;
    long senderID, receiverID ;
    int conversionNumber = 1 ;
    int chatID = 0 ;
    int senderMessageID, receiverMessageID ;
    int userChoice = 1 ;
    FILE *filePointerSender, *filePointerReceiver ;
    struct Message message ;

    // Welcome screen message
    printf("#################################################################\n");
    printf("###### Hey there human! Welcome to my ChatApp!! WAZZUP!?!!!###### \n") ;
    printf("#################################################################\n");
    printf("\t I would like to know your ChatApp Name : ") ;
    scanf("%s" ,sender) ;

    // Convert string to long(ascii)
    for(int count = 0 ; sender[count] != '\0' ; count++)
    {
        long stringToLong = (sender[count] - 32) ;
        chatID = (chatID + (stringToLong * conversionNumber)) ;
        conversionNumber = (conversionNumber * 100) ;
    }
    senderID = chatID ;
    system("clear") ;
    while(userChoice != 4)
    {
        // Home Screen options for user
        printf("\n\n\t\t" "Hello %s, What would you like to do today? \n\n\t\t"
               "1.) I want to Chat" "\n\t\t"
               "2.) Show my Messages.." "\n\t\t"
               "3.) Show my Chat History.." "\n\t\t"
               "4.) I'm done, Get me OUTTA here!" "\n\n\t\t"
               "This is a ONE WORD ChatApp, Concatenate words using UNDERSCORE!\n\t\t"
               "Press 1, 2, 3 or 4 followed by ENTER KEY!\n\n\t\t"
               "Hey %s! I'm waiting for your input : ", sender, sender) ;
       scanf("%d", &userChoice) ;


       // Handled user options for Chatting, Received Messages, Message History and Exit Application respectively
       switch(userChoice)
       {
       case 1:
           // Chat Option
           printf("I want to chat with : ") ;
           scanf("%s", receiver) ;
           chatID = 0 ;
           conversionNumber = 1 ;

           for (int count = 0 ; receiver[count] != '\0' ; count++)
           {
               long stringToLong = (receiver[count] - 32) ;
               chatID = (chatID + (stringToLong * conversionNumber)) ;
               conversionNumber = (conversionNumber * 100) ;
           }
           receiverID = chatID ;

           receiverMessageID = msgget((key_t)receiverID, 0666 | IPC_CREAT) ;

           if(receiverMessageID == -1)
           {
               system("clear") ;
               printf("EHH! ERROR!! Could not create Message ID for %s! Exiting ChatApp :( \n", receiver) ;
               exit(EXIT_FAILURE) ;
           }

           int flag = 1 ;

           filePointerReceiver = fopen(receiver, "a") ;

           if(filePointerReceiver == NULL)
           {
               system("clear") ;
               printf("EHH! ERROR!! Could not create Chat file! Exiting ChatApp :( \n") ;
               exit(EXIT_FAILURE) ;
           }

           filePointerSender = fopen(sender, "a") ;

           if(filePointerSender == NULL)
           {
               system("clear") ;
               printf("EHH! ERROR!! Could not create Alias file! Exiting ChatApp :( \n") ;
               exit(EXIT_FAILURE) ;
           }

           fprintf(filePointerSender, "\n");
           fprintf(filePointerSender, "Sending message to : < %s >", receiver) ;
           fprintf(filePointerSender, "\n") ;
           fprintf(filePointerReceiver, "\n") ;
           fprintf(filePointerReceiver, "Received message from : < %s >", sender) ;
           fprintf(filePointerReceiver, "\n") ;

           printf("Hey %s! You can type your message here \n", sender) ;

           while(flag)
           {
               printf("< %s > say's : ", sender) ;
               scanf("%s", chatBuffer) ;

               message.messageType = 1 ;
               strcpy(message.messageBody.name, sender) ;
               strcpy(message.messageBody.body, chatBuffer) ;

               if(msgsnd(receiverMessageID, (void *)&message, MAX_CHAR, 0) == -1)
               {
                   printf("EHH! ERROR!! Could not send message. Exiting ChatApp :( \n") ;
                   exit(EXIT_FAILURE) ;
               }

               fprintf(filePointerSender, "\t >>>> %s \n", chatBuffer) ;
               fprintf(filePointerReceiver, "\t >>>> %s \n", chatBuffer) ;

               if(strncmp(chatBuffer, "CIAO", 4) == 0)
               {
                   flag = 0 ;
                   system("clear")  ;
               }
           }

           fclose(filePointerSender) ;
           fclose(filePointerReceiver) ;
        break ;

       case 2:
           // Received Messages
           system("clear") ;
           printf("Hey %s! You have these messages! O_o? \n", sender) ;
           senderMessageID = msgget((key_t)senderID, 0666 | IPC_CREAT) ;

           if(senderMessageID == -1)
           {
               printf("EHH! ERROR!! Could not create Message ID. Exiting ChatApp :( \n") ;
               exit(EXIT_FAILURE) ;
           }

           int receiveFlag = 1;
           while(receiveFlag)
           {
               if(msgrcv(senderMessageID, (void *)&message, BUFFER_SIZE, 0, IPC_NOWAIT) == -1)
               {
                   printf("%s is a LoneWolf!! You haven't received any messages! x_x \n", sender) ;
                   break ;
               }

               printf("< %s > said : %s \n", message.messageBody.name, message.messageBody.body) ;

               if(strncmp(message.messageBody.body, "CIAO", 4) == 0)
               {
                   receiveFlag = 0;
               }
           }
        break ;

       case 3:
           // Message History
           system("clear") ;
           filePointerSender = fopen(sender, "r") ;
           if(filePointerSender == NULL)
           {
               printf("%s is a LoneWolf!! You have NO message history! x_x \n", sender) ;
               break ;
           }


        while(1337)
        {
            char myChar = fgetc(filePointerSender) ;

            if(feof(filePointerSender))
                break;

            printf("%c", myChar) ;
        }

        fclose(filePointerSender) ;
        break ;

       case 4:
           // Exit Application
           system("clear") ;
           printf("CIAO! Until next time! Come back soon! \n") ;
        break ;

       default:
           system("clear") ;
           printf("Good try %s, But we do not provide that option! ~_~\n", sender);
           printf("Let's try that one more time! \n");
       }
    }
    return 0 ;
}
