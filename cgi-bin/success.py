import cgi, cgitb, urllib2

def success():
    resourcesLoc = './resources.csv'
    try:
        """ we open the resources file and
            extract the numbers stored in it.
            we overwrite the file and change the 
            1 at the end, which denotes occupied, 
            to 0 (not occupied) """
        input_file = open(resourcesLoc, "r")
        details = input_file.readlines()
        detailsLine1 = details[0]
        detailsLine1 = detailsLine1.replace(" ", "")
        resources = detailsLine1.split(',')
        output_file = open(resourcesLoc, "w")
        output_file.write(resources[0] + "," + resources[1] + "," + '0')
    
    except IOError:
        print "Cannot open file"
    
    finally:
        input_file.close()
        output_file.close()

success()
