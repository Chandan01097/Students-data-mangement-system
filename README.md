
# 🎓 Student Management System (C Project)

##  About This Project
This is a simple yet functional **Student Management System** written in C. It's got all the essentials: add students, update them, delete them, and even let them log in to see their own info. We’ve even got an Admin login, so only the boss can make changes. Plus, it auto-saves everything to a CSV file for easy tracking and reporting.

## 🚀 Features
- 🔐 **Admin Authentication** (password-protected)
- 📝 **Add / Insert Student Record**
- 🧑‍🎓 **Student Login** (with personal password)
- ✏️ **Update Student Record**
- ❌ **Delete Student Record**
- 📄 **Display All Students in a Fancy Table**
- 💾 **Auto-Save to CSV File (with Fees Due calculation)**
- 📂 **Auto-Load Records from CSV File on Startup**

## 🗃️ CSV File Structure
When saved, your `Students.csv` will look like this:
```
Roll No.,Name,Phone,Percentage,Fees Paid,Fees Due,Password
101,John Doe,9876543210,85.5,100000.00,75000.00,john123
...
```

## 🏗️ Tech Stack
- C (Standard C Libraries)
- CSV file for data persistence
- Terminal/Command-line interface (CLI)

## 🔑 Admin Login
- **Username:** Admin (hardcoded)
- **Password:** `admin$123`

## 🛣️ How It Works
1. Admin logs in to manage student records.
2. Students can log in individually to view their personal details.
3. The system auto-saves all data to `Students.csv` after each operation.
4. Pending (due) fees are calculated automatically based on an annual fee of ₹175,000.

## 📌 Notes
- The project saves the CSV file at:  
  `C:\Users\cb131\OneDrive\Desktop\Students.csv`  
  You can change this in the `#define FILE_PATH` macro.
- No fancy databases, just good old CSV magic!
- Works on Windows (due to file path formatting), tweak the path if you're on Linux/Mac.


