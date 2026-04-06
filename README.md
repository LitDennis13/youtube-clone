# youtube-clone

## How to run

### To start the frontend
* Navigate to the "youtube-clone" folder in the terminal
* cd into the "youtube-clone-frontend" folder
* run the command "npm build"
* run the command "npm start"
* There should now be a local host address displayed
* copy the address and paste into broswer address bar and press enter

### To start the backend
* Navigate to the "youtube-clone" folder in the terminal
* cd into the "youtube-clone-backend" folder
* run the command "./run.sh"

### How to run MySQL Database
* run "docker compose down -v"
* run "docker compose up -d"

### How to access MySQL Database from command line
* Do steps from previous section
* run "docker exec -it youtube-clone-mysql-database /bin/bash"
* run "mysql -u root -p"
* check ".env" file for passwords
* run "show databases;" to show databases
* run "use youtube-clone-database"
* run "show tables;"
