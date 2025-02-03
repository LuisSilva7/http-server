# HTTP Server

This is a minimal multi-threaded HTTP server built in C. It supports basic HTTP methods and can handle multiple connections concurrently.

## Features

- **Supports HTTP methods**: `GET`, `POST`, `PUT`, and `DELETE`.
- **Multi-threaded processing**: Uses `pthread` to handle multiple client connections simultaneously.
- **Static file serving**: Serves files from the `static/` directory.
- **Request handling**: Parses HTTP requests and responds with appropriate status codes.
- **File operations**: Reads, writes, and deletes files dynamically based on requests.

## Technologies Used

- **C**: Core programming language.
- **POSIX Sockets**: For handling network communication.
- **pthread**: Multi-threading to manage concurrent client connections.

## How to Run the Project Locally

### Installation Steps

1. **Clone the repository:**
   ```bash
   git clone https://github.com/LuisSilva7/http-server.git
   ```
   
2. **Navigate to the project directory:**

   ```bash
   cd http-server
   ```

3. **Compile the project:**

   ```bash
   make
   ```

4. **Run the server:**

   ```bash
   make run
   ```

The server will start and listen on port 8080. You can test it with:

  ```bash
  curl -X GET http://localhost:8080/
  curl -X POST http://localhost:8080/static/test.txt -d "This is a test file"
  curl -X PUT http://localhost:8080/static/test.txt -d "Updated content"
  curl -X DELETE http://localhost:8080/static/test.txt
  ```






