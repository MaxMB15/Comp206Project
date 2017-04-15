import cgi, cgitb, urllib2
from subprocess import call

def transport():
    """ From the form on the web page,
        we get the player's inventory
        and the url of the room that
        they came from """
    form = cgi.FieldStorage()
    inventoryVals = form.getvalue('inventory')
    url = form.getvalue('url')
    inventoryVals = inventoryVals + ''
    inventoryAsList = inventoryVals.split(',')
    mana = inventoryAsList[0]
    gold = inventoryAsList[1]
    
    """ resources.csv is stored in the
        same place as transporter.py and
        room.cgi is stored in the same
        place as well """
    resourcesLoc = './resources.csv'
    roomLoc = './room.cgi'

    try:
        """ we access the resources file and
            get the last number which tells us
            if the room is occupied or not """
        input_file = open(resourcesLoc, "r")
        details = input_file.readlines()
        detailsLine1 = details[0]
        detailsLine1 = detailsLine1.replace(" ", "")
        resources = detailsLine1.split(',')
        occupiedOrNot = int (resources[2])

        """ if the room is occupied we send
            the player back to the room where
            they came from by calling the program
            on the previous website """
        if occupiedOrNot == 1:
            
            print 'Content-Type:text/html\n\n'
            print '<html>'
            print '    <title>We Love Poems!</title>'
            print '    <body>'
            print '       <center>'
            print '            <div>'
            print '                <h1>'
            print '                    <p><font color=\"white\">Sorry, the room is occupied. Click the button to go back.</font></p>'
            print '                </h1>'
            print '     			  <form action=\"%s\" method=\"POST\"><input type=\"submit\"></input><input type=\"hidden\" name=\"command\" value=\"REFRESH\"></input><input type=\"hidden\" name=\"inventory\" value=\"%s,%s\"></input></form>' %url %mana %gold 
            print '            </div>'
            print '        </center>'
            print '    </body>'
            print '    <style>'
            print '        @font-face {'
            print '            font-family: Distant_Stroke;'
            print '            src: url(\"../src/Distant_Stroke.otf\") format(\"opentype\");'
            print '        }'
            print '        body {'
            print '            height: 100%%;'
            print '            margin: 0;'
            print '            padding: 0;'
            print '            background-color: #FFCC00;'
            print '            background: url(\"../src/bg.jpg\"'
            print '            background-size: 100%% 100%%;'
            print '            font-family: Distant_Stroke;'
            print '            font-size: 30px;'
            print '        }"
            print '        input[type=submit] {'
            print '            width: 20%%;  height: 10%%;'
            print '            font-family: Distant_Stroke;'
            print '            font-size: 40px;'
            print '            text-align: center;'
            print '        }'
            print '    </style>'
            print '</html>'

        else:
            """ if the room is not occupied, we
                change our resources to reflect
                that it is now occupied and we
                print out the webpage """
            
            print 'Content-Type:text/html\n\n'
            print '<html>'
            print '    <title>We Love Poems!</title>'
            print '    <body>'
            print '       <center>'
            print '            <div>'
            print '                <h1>'
            print '                    <p><font color=\"white\">Our room is empty! We welcome you to our beautiful room!</font></p>'
            print '                </h1>'
            print '     			  <form action=\"%s\" method=\"POST\"><input type=\"submit\"></input><input type=\"hidden\" name=\"command\" value=\"JOIN\"></input><input type=\"hidden\" name=\"inventory\" value=\"%s,%s\"></input></form>' %roomLoc %mana %gold 
            print '            </div>'
            print '        </center>'
            print '    </body>'
            print '    <style>'
            print '        @font-face {'
            print '            font-family: Distant_Stroke;'
            print '            src: url(\"../src/Distant_Stroke.otf\") format(\"opentype\");'
            print '        }'
            print '        body {'
            print '            height: 100%%;'
            print '            margin: 0;'
            print '            padding: 0;'
            print '            background-color: #FFCC00;'
            print '            background: url(\"../src/bg.jpg\"'
            print '            background-size: 100%% 100%%;'
            print '            font-family: Distant_Stroke;'
            print '            font-size: 30px;'
            print '        }"
            print '        input[type=submit] {'
            print '            width: 20%%;  height: 10%%;'
            print '            font-family: Distant_Stroke;'
            print '            font-size: 40px;'
            print '            text-align: center;'
            print '        }'
            print '    </style>'
            print '</html>'
    
    except IOError:
        print 'Cannot open file'

    finally:
        input_file.close()
        output_file.close()
        html_file.close()
    

transport()