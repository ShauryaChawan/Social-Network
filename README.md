
<hr/>

# Schema

Social Netowrk{
  Member Variables:
  map Posts = [
    postId: [
      userId:userId, 
      postCreateDateTime:postCreateDateTime, 
      postContent:postContent
    ],
  ]

  map User = [
    userId: [
      userFirstName:userFirstName, 
      userLastName:userLastName, 
      userName:userName, 
      userAge:userAge, 
      userPassword,
      posts:[postId, postId, postId, postId,]
      friends: [userId, userId, userId, userId, userId]
    ]
  ]
  Member Function:
    1. Register
    2. Login
    3. Logout
    4. Display Your Profile
    5. Display All Your Friends (Only Full Name (Firstname + lastname + age))
    6. Display All Available Users in the Platform
    7. Add a Friend (userId should be passed to this function)
    8. Unfriend a Friend
    9. Delete Account
    10. Create a Post
    11. See All Your Posts
    12. Get a Single Post
    13. Delete a Post (Your)
    14. Edit a Post (Your)
    15. See Posts (your's and friend's posts)
    16. Exit
  }

It is a menu-driven console-based application using a 'while' loop and 'switch' statements. 

When the program first runs only the following actions should be displayed to the user:
1. Register
2. Login
3. Exit

If the user chooses '1' then after registering, the user should get the option of :
1. Login.
2. Exit

After 'Login', the user should get the following options:
1. Logout
2. Display Your Profile
3. Display All Your Friends (Only Full Name (Firstname + lastname))
4. Display All Available Users n the Platform
5. Add a Friend
6. Unfriend a Friend
7. Delete Account
8. Create a Post
9. See All Your Posts
10. Get a Single Post
11. Delete a Post (Your)
12. Edit a Post (Your)
13. See Posts (your's and friend's posts)
14. Exit