for file in `find ./ -name "*.hpp"`
do
   #wc -l $file;
   sed -i '' 's/unsigned\ int/uint/g' $file;
   #stat -c %s $file;
done
