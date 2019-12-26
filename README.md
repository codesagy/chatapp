# ChatApp using Unix system V IPC message queue.

Problem statement: Write a chat application using Unix system V IPC message queue. 
The chat application should have following features: User should able to :

1. Specify his name(chat alias) when your application runs
2. Chat with another user using a username.
3. View his messages based your username entered in step 1.
4. Should able to see messages received from all users.
5. Optional feature: Save chat history on disk in a file with username and allow 
   user to read it later through your program.

Programming aspects:

    Message queue will help to keep sent messages in the system buffer, 
	so that even if your application terminates, when you'll run your application later, 
	you can see your unread(newly received) messages.

    Code should have proper error handling. Especially while creating, using the message queue.

    You can read, reply when you send a message or have a separate thread to 
	monitor the queue for incoming messages(optional).

    Single program should serve the purpose. No dedicated chat server is needed.

# Instructions to use ChatApp :
1.  I want to Chat
    - Use 'CIAO' to exit sending messages.
2.  Show my Messages..
    - Use this option repeatedly to display received messages until you have no incoming messages left.
3.  Show my Chat History..
    - Use this option to get your chat history.
4.  I'm done, Get me OUTTA here!
    - Exit chat application.




