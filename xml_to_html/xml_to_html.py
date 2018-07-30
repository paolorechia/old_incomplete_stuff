import sys



def main(xml_file):


    last_dot = len(xml_file) - 3
    file_format = xml_file[last_dot:]
    file_name = xml_file[:last_dot]
    print(file_name)
    print(file_format)
    if (file_format != "xml"):
        print("Please provide a file with .xml extension (filename.xml)")
    print("Opening... " + xml_file)
    
    f_input = open(xml_file, "r")
    output_file_name = file_name + "html"

    print("Creating..." +output_file_name)
    f_output = open(output_file_name, "w")


    # read header
    for i in range(3):
        input_line =f_input.readline()
#        print(input_line)

    tags_dict = {'para': '<p>', '/para': '</p>', 'para/': '<p></p>',
                 'orderedlist': '<ol>', '/orderedlist': '</ol>',
                 'orderedlist/': '<ol></ol>',
                 'listitem': '<li>', '/listitem': '<li>',
                 'listitem/': '<li></li>',
                 'article': '',
                 '/article': ''}

    while(input_line != ""):
        input_line = f_input.readline()
        tag_start = 0
        list_start = []
        list_end = []
        counter = -1
        while (tag_start != -1):
            if (counter == -1):
                counter = 0
                tag_start = input_line.find("<")
                list_start.append(tag_start)
                tag_end = input_line.find(">")
                list_end.append(tag_end)

            else:
                tag_start = input_line.find("<", list_start[counter] + 1)
                list_start.append(tag_start)
                tag_end = input_line.find(">", list_end[counter] + 1)
                list_end.append(tag_end)
                counter += 1
#                print(list_start)
#                print(list_end)

# display tags and text
        j = 0
        for i in range(len(list_start) - 1):
            if list_start[i] != -1:
                tag = input_line[list_start[i]+1:list_end[j]]
#                print(tag)
#                print(tags_dict[tag])
                f_output.write(tags_dict[tag])
                

                if (list_start[i + 1] != -1):
                    output_line = input_line[list_end[j] + 1:list_start[i+1]]
#                    print output_line
                    f_output.write(output_line)
                j += 1



#        print(input_line)




    f_input.close()
    f_output.close()
    



if __name__ == "__main__":
    
    if (len(sys.argv) != 2):
        print("Usage: " + sys.argv[0] + " xml_file.xml")
    else:
        main(sys.argv[1])
