#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

void clearInputBuffer()
{
  cin.clear();                                         // Clear the error flag
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
}

class SocialNetwork
{
private:
  // postId: [userId, postCreateDateTime, postContent]
  map<int, vector<string>> posts;
  // userId: [userFirstName, userLastName, userName, userAge, userPassword, posts]
  map<int, vector<string>> users;

  int currentUserID; // To keep track of the current user

public:
  SocialNetwork() : currentUserID(-1) {}

  void registerUser();
  void loginUser();
  void logoutUser();
  void displayYourProfile();
  void displayAllAvailableUsers();
  void deleteAccount();
  void createPost();
  void getSinglePost(int postID);
  void deleteYourPost(int postID);
  void editYourPost(int postID);
  void seePosts();
  void displayMainMenu();
  void displayUserMenu();
};

void SocialNetwork::registerUser()
{
  string firstName, lastName, password;
  int age;

  cout << "-> Enter your first name: ";
  cin >> firstName;

  cout << "-> Enter your last name: ";
  cin >> lastName;

  cout << "-> Enter your age: ";
  cin >> age;

  string userName = firstName + "_" + lastName + "_" + to_string(age);

  cout << "-> Create a password: ";
  cin >> password;

  int newUserID = users.size() + 1;
  users[newUserID] = {firstName, lastName, userName, to_string(age), password, "", ""};

  cout << "--> !! Registration successful !!\n";
  cout << "--> User User Name is: " + userName << endl;
}

void SocialNetwork::loginUser()
{
  string userName, password;

  cout << "-> Enter your username: ";
  cin >> userName;

  cout << "-> Enter your password: ";
  cin >> password;

  for (const auto &user : users)
  {
    if (user.second[2] == userName && user.second[4] == password)
    {
      currentUserID = user.first;
      cout << "--> !! Login successful !!\n";
      return;
    }
  }

  cout << "--> # Invalid username or password. #\n";
}

void SocialNetwork::logoutUser()
{
  currentUserID = -1;
  cout << "--> !! Logout successful !!\n";
}

void SocialNetwork::displayYourProfile()
{
  if (currentUserID != -1)
  {
    cout << "->Your Profile:\n";
    const auto &user = users[currentUserID];
    cout << "\t-->Name: " << user[0] << " " << user[1] << "\n";
    cout << "\t-->Username: " << user[2] << "\n";
    cout << "\t-->Age: " << user[3] << "\n";
    cout << "\t-----"<<endl;
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::displayAllAvailableUsers()
{
  if (currentUserID != -1)
  {
    cout << "-> Available Users:\n";
    int count = 0;
    for (const auto &user : users)
    {
      if (user.first != currentUserID)
      {
        count++;
        cout << "\t-->User " << count << ": " << endl;
        cout << "\t\t-->User ID: " << user.first << endl;
        cout << "\t\t-->Name: " << user.second[0] << " " << user.second[1] << endl;
        cout << "\t\t-->(User Name: " << user.second[2] << ")," << endl;
        cout << "\t\t-->(Age: " << user.second[3] << ")\n";
        cout << "\t---\n";
      }
    }
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::deleteAccount()
{
  if (currentUserID != -1)
  {
    users.erase(currentUserID);
    cout << "--> !! Account deleted successfully !!\n";
    logoutUser();
  }
  else
  {
    cout << "-> # Please log in first. #\n";
  }
}

void SocialNetwork::createPost()
{
  if (currentUserID != -1)
  {
    cout << "-> Enter your post content: ";
    string postContent;
    cin.ignore(); // Clear the newline from the buffer
    getline(cin, postContent);

    time_t currentTime = time(0);
    tm *now = localtime(&currentTime);
    char timeBuffer[80];
    strftime(timeBuffer, sizeof(timeBuffer), "%d %b, %Y", now);

    int newPostID = posts.size() + 1;
    posts[newPostID] = {to_string(currentUserID), timeBuffer, postContent};

    auto &userPosts = users[currentUserID][5]; // Assuming posts are stored at index 5
    userPosts += to_string(newPostID) + " ";

    cout << "--> !! Post created successfully !!\n";
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::getSinglePost(int postID)
{
  if (posts.find(postID) != posts.end())
  {
    const auto &post = posts[postID];
    const auto &user = users[stoi(post[0])];
    cout << "\t---\n";
    cout << "\t--> Post ID: " << postID << "\n";
    cout << "\t--> Author: " << user[2] << "\n";
    cout << "\t--> Content: " << post[2] << "\n";
    cout << "\t--> Created at: " << post[1] << "\n";
  }
  else
  {
    cout << "--> # Post not found. #\n";
  }
}

void SocialNetwork::deleteYourPost(int postID)
{
  if (currentUserID != -1)
  {
    auto &userPosts = users[currentUserID][5]; // Assuming posts are stored at index 5
    size_t pos = userPosts.find(to_string(postID));
    if (pos != string::npos)
    {
      userPosts.erase(pos, to_string(postID).length() + 1);
      posts.erase(postID);
      cout << "--> !! Post deleted successfully !!\n";
    }
    else
    {
      cout << "--> # You are not authenticated to delete the post or the post is not found. #\n";
    }
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::editYourPost(int postID)
{
  if (currentUserID != -1)
  {
    auto &userPosts = users[currentUserID][5]; // Assuming posts are stored at index 5
    size_t pos = userPosts.find(to_string(postID));
    if (pos != string::npos)
    {
      auto &post = posts[postID];
      cout << "-> Enter the new content for your post: ";
      string newContent;
      cin.ignore(); // Clear the newline from the buffer
      getline(cin, newContent);
      post[2] = newContent;
      cout << "--> !! Post edited successfully !!\n";
    }
    else
    {
      cout << "--> # You are not authenticated to delete the post or the post is not found. #\n";
    }
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::seePosts()
{
  if (currentUserID != -1)
  {
    cout << "-> Posts:\n";
    for (const auto &post : posts)
    {
      getSinglePost(post.first);
    }
  }
  else
  {
    cout << "--> # Please log in first. #\n";
  }
}

void SocialNetwork::displayMainMenu()
{
  int choice;
  do
  {
    cout << "\n------Social Network------\n";
    cout << "\n---   Welcome Main   ---\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "---\n";
    cout << "Enter your choice: ";
    // cin >> choice;

    if (!(cin >> choice))
    {
      cout << "Invalid input. Please enter a number.\n";
      clearInputBuffer(); // Clear the input buffer
      continue;
    }

    switch (choice)
    {
    case 1:
      registerUser();
      break;
    case 2:
      loginUser();
      if (currentUserID != -1)
      {
        displayUserMenu();
      }
      break;
    case 3:
      cout << "Exiting the application.\n";
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
      break;
    }
  } while (choice != 3);
}

void SocialNetwork::displayUserMenu()
{
  int choice;
  do
  {
    cout << "\n------Social Network------\n";
    cout << "\n---   Welcome Main   ---\n";
    cout << "1. Logout\n";
    cout << "2. Display Your Profile\n";
    cout << "3. Display All Available Users\n";
    cout << "4. Delete Account\n";
    cout << "5. Create a Post\n";
    cout << "6. Get a Single Post\n";
    cout << "7. Delete a Post (Your)\n";
    cout << "8. Edit a Post (Your)\n";
    cout << "9. See Posts (yours and friends)\n";
    cout << "10. Exit\n";
    cout << "---\n";
    cout << "Enter your choice: ";
    // cin >> choice;

    if (!(cin >> choice))
    {
      cout << "Invalid input. Please enter a number.\n";
      clearInputBuffer(); // Clear the input buffer
      continue;
    }

    switch (choice)
    {
    case 1:
      logoutUser();
      break;
    case 2:
      displayYourProfile();
      break;
    case 3:
      displayAllAvailableUsers();
      break;
    case 4:
      deleteAccount();
      break;
    case 5:
      createPost();
      break;
    case 6:
      cout << "Enter the post ID to view: ";
      int viewPostID;
      cin >> viewPostID;
      getSinglePost(viewPostID);
      break;
    case 7:
      cout << "Enter the post ID to delete: ";
      int deletePostID;
      cin >> deletePostID;
      deleteYourPost(deletePostID);
      break;
    case 8:
      cout << "Enter the post ID to edit: ";
      int editPostID;
      cin >> editPostID;
      editYourPost(editPostID);
      break;
    case 9:
      seePosts();
      break;
    case 10:
      cout << "Exiting the application.\n";
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 10);
}

int main()
{
  SocialNetwork socialNetwork;
  socialNetwork.displayMainMenu();

  return 0;
}
