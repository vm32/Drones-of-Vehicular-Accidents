import requests
import re
import os
import json
from github import Github

# Replace with your own GitHub access token
access_token = "YOUR_GITHUB_ACCESS_TOKEN"

# Replace with your own GitHub repository name and path
repo_name = "YOUR_REPOSITORY_NAME"
file_path = "path/to/file.txt"

# Replace with the URL that contains the latitude and longitude numbers and the database
url = "https://example.com/latlong=12.34,-56.78"

response = requests.get(url)
lat_long = re.search(r'latlong=([\d.-]+)', response.text)
if lat_long:
    lat, long = lat_long.group(1).split(',')
    print(f"Latitude: {lat}, Longitude: {long}")
    # Connect to GitHub
    g = Github(access_token)
    user = g.get_user()
    repo = user.get_repo(repo_name)
    # Create or update the file
    repo.create_file(file_path, "Adding lat and long numbers", f"{lat}, {long}")
else:
    print("Latitude and longitude numbers not found in the URL.")
