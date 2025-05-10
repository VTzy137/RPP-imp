#!/bin/bash
echo "Building React app..."
cd my-react-app
npm run build
cd ..

echo "Copying files to root directory..."
cp -r my-react-app/build/static .
cp my-react-app/build/*.{ico,png,json} .

echo "Fixing paths in index.html..."
sed -i 's|href="/rpp-imp/|href="./|g; s|src="/rpp-imp/|src="./|g' index.html

echo "Committing changes..."
git add .
git commit -m "Update website with latest changes"

echo "Pushing to GitHub..."
git push origin gh-pages

echo "Done! Your site will be updated shortly at https://vtzy137.github.io/RPP-imp/"
