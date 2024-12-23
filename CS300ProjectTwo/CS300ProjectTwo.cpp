#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// Course class to store course details 
class Course {
public:
    std::string course_number;
    std::string course_title;
    std::vector<std::string> prerequisites;

    Course(std::string num, std::string title, std::vector<std::string> prereqs)
        : course_number(num), course_title(title), prerequisites(prereqs) {}
};

// Function to convert a string to uppercase to ensure that lowercase inputs can be considered
std::string toUpperCase(const std::string& str) {
    std::string upperStr = str;  // Make a copy of the string
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);  // Convert each character to uppercase in the course number
    return upperStr;
}

// Function to load course data from the designated csv file
void loadData(const std::string& filename, std::vector<Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> course_data;

        // Split line by commas
        while (std::getline(ss, item, ',')) {
            course_data.push_back(item);
        }

        // Ensure line has enough data to cover the prerequisite basis
        if (course_data.size() < 2) {
            std::cerr << "Error: Invalid line format." << std::endl;
            continue;
        }

        std::string course_id = course_data[0];
        std::string course_title = course_data[1];
        std::vector<std::string> prerequisites(course_data.begin() + 2, course_data.end());

        // Create a new Course object and add it to the vector
        Course course(course_id, course_title, prerequisites);
        courses.push_back(course);
    }

    file.close();
}

// Function to print sorted course list
void printSortedCourses(const std::vector<Course>& courses) {
    std::vector<Course> sorted_courses = courses;  // Make copy for sorting
    std::sort(sorted_courses.begin(), sorted_courses.end(), [](const Course& a, const Course& b) {
        return a.course_number < b.course_number;  // alphanumeric sorting
        });

    for (const auto& course : sorted_courses) {
        std::cout << course.course_number << ": " << course.course_title << std::endl;
    }
}

// Function to print course details based on course number
void printCourseDetails(const std::string& course_number, const std::vector<Course>& courses) {
    std::string course_number_upper = toUpperCase(course_number);  // Convert input to uppercase

    for (const auto& course : courses) {
        if (toUpperCase(course.course_number) == course_number_upper) {  // Compare in uppercase
            std::cout << "Course ID: " << course.course_number << "\n";
            std::cout << "Title: " << course.course_title << "\n";
            std::cout << "Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << "\n";
            return;
        }
    }

    std::cout << "Course not found." << std::endl;
}

int main() {
    std::vector<Course> courses;  // Vector to store all courses
    std::string filename;
    int option;
    std::string course_number;

    while (true) {
        // Display menu options
        std::cout << "1: Load file data\n";
        std::cout << "2: Print sorted course list\n";
        std::cout << "3: Print course details\n";
        std::cout << "9: Exit\n";
        std::cout << "Enter option: ";
        std::cin >> option;
        std::cin.ignore();  // Ignore any leftover newline character

        switch (option) {
        case 1:
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);  // Get the filename from user
            loadData(filename, courses);  // Load data into the vector
            break;
        case 2:
            printSortedCourses(courses);  // Print sorted course list
            break;
        case 3:
            std::cout << "Enter course number: ";
            std::getline(std::cin, course_number);  // Get the course number from user
            printCourseDetails(course_number, courses);  // Print course details
            break;
        case 9:
            std::cout << "Exiting program.\n";
            return 0;  // Exit the program
        default:
            std::cout << "Invalid option. Try again.\n";  // Handle invalid menu options
        }
    }

    return 0;
}


