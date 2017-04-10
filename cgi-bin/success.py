import cgi, cgitb, urllib2

def success():
    resourcesLoc = "http://cs.mcgill.ca/~mrunds/Game/resources.csv"
    input_file = urllib2.urlopen(resourcesLoc)
    details = input_file.readlines()
    detailsLine1 = details[0]
    detailsLine1 = detailsLine1.replace(" ", "")
    # print detailsLine1
    resources = detailsLine1.split(',')
    # print occupiedOrNot
    # output_file = (resourcesLoc, "w")
    output_file = open("fromWeb.txt", "w")
    # output_file.write("hello")
    output_file.write(resources[0] + "," + resources[1] + "," + '0')
    output_file.close()

success()
