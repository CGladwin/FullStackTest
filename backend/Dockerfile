# backend/Dockerfile
FROM node:16

WORKDIR /app

# Install build tools for C++
RUN apt-get update && apt-get install -y g++ make

# Copy package.json and install dependencies
COPY package.json .
RUN npm install

# Copy the rest of the application files
COPY . .

# Compile the C++ program
WORKDIR /app/cpp
RUN make

WORKDIR /app

# Create the uploads directory
RUN mkdir -p uploads && chmod -R 777 uploads

EXPOSE 3000
CMD ["node", "app.js"]