while inotifywait -r -e modify,create,delete .; do
    make test
done