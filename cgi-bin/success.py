import cgi, cgitb, urllib2

def success():
    resourcesLoc = 'http://cs.mcgill.ca/~mrunds/Game/resources.csv'
    try:
        input_file = open(resourcesLoc, "r")
        details = input_file.readlines()
        detailsLine1 = details[0]
        detailsLine1 = details.replace(" ", "")
        # print detailsLine1
        resources = detailsLine1.split(',')
        # print occupiedOrNot
        output_file = open(resourcesLoc, "w")
        output_file.write(resources[0] + "," + resources[1] + "," + '0')
    
    except IOError:
        print 'Cannot open file'

    finally:
	input_file.close()
	output_file.close()

success()
