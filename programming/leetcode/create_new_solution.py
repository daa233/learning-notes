# Prepare a new solution for LeetCode problem
# This script is inspired by Hao Chen's shell scripts
# (https://github.com/haoel/leetcode/tree/master/scripts) and based on Ma Xiaoyang's Python scripts
# (https://github.com/xapcloud/Code-Grab-from-Leetcode)


from __future__ import print_function
import requests
import json
from bs4 import BeautifulSoup
import html2text
import textwrap
import os
import datetime
import argparse

parser = argparse.ArgumentParser(description='Prepare a new solution for LeetCode problem')
parser.add_argument('--id', dest='id', default='0', type=int,
                    help='specify the problem id')
parser.add_argument('--update_list', '--update', dest='update', action='store_true',
                    help='update the problems list json file')
parser.add_argument('--lang', '--language', dest='lang', default='c++', type=str,
                    help='language option: c, c++, python')

problems_list_base_url = 'https://leetcode.com/api/problems/'
category_slug = 'all'   # option: all, algorithms, database, shell
problem_base_url = 'https://leetcode.com/problems/'
problems_list_json_filename = 'problems_list.json'
solution_base_path = './'
author_name = 'Du Ang'
date = datetime.date.today().strftime('%b %d, %Y')

# Parse the arguments
args = parser.parse_args()


class Problem(object):
    def __init__(self, id):
        self.stat = {
            'id': id,
            'title': None,
            'title_slug': None,
            'description': None,
            'url': None,
            'paid_only': None
        }

    def set_value(self, key, value):
        self.stat[key] = value

    def get_stat(self, problems_list_json_filename):
        '''
        Find the problem's slug in the problems list json file, according to the problem id.
        Get the problem statistics according to the problem title.
        '''

        # Load problems list and convert it to dictionary
        with open(problems_list_json_filename, 'rb') as f:
            problems_list_str = f.read().decode()
            data_json = json.loads(problems_list_str)
            # Get the problems list
            problems_list = data_json['stat_status_pairs']

        # Traverse the problems list and get the args.id-th problem
        found_flag = False
        for problem_item in problems_list:
            if problem_item['stat']['frontend_question_id'] == self.stat['id']:
                found_flag = True
                problem_title_slug = problem_item['stat']['question__title_slug']
                self.set_value('title_slug', problem_title_slug)
                self.set_value('title', problem_item['stat']['question__title'])
                self.set_value('url', problem_base_url+problem_title_slug)
                self.set_value('paid_only', problem_item['paid_only'])

        if found_flag:
            if self.stat['paid_only']:
                exit('==> ERROR: Problem {} is paid only.'.format(args.id))

            print('==> Found problem  {}. {}'.format(args.id, problem_title_slug))
            # Send requests and get the response page
            try:
                problem_response = requests.get(problem_base_url+problem_title_slug)
                # Parse the response page
                problem_page = BeautifulSoup(problem_response.text, 'html.parser')
                # Get the description of the problem
                for meta in problem_page.find_all('meta'):
                    if meta.get('name') == 'description':
                        description_text = meta.get('content')
                        description_text = html2text.html2text(description_text)
                        problem.set_value('description', description_text)
                problem_response.close()
            except (requests.exceptions.ReadTimeout,requests.exceptions.ConnectTimeout):
                exit('==> ERROR: Time out!')
        else:
            exit('==> ERROR: Unable to find problem {}'.format(args.id))


def get_problems_list_json_file(problems_list_json_filename):
    '''
    Get the problems list json file.
    If problems list json file does not exist, send requests, get responses and save it.
    '''
    try:
        r = requests.get(url=problems_list_base_url + category_slug)
        # Write to json file 'problems_list.json'
        with open(problems_list_json_filename, 'w') as f:
            f.write(r.text)
        r.close()
    except (requests.exceptions.ReadTimeout,requests.exceptions.ConnectTimeout):
        exit('==> ERROR: Time out!')


def create_new_solution(problem, solution_base_path, author_name, date, file_type='cpp'):
    '''
    According to the problem id, get the problem contents and write them to the solution
    file with specific type.
    '''
    solution_path = solution_base_path + str(problem.stat['id']) + '-' \
                    + problem.stat['title_slug'] + '/'
    if not os.path.isdir(solution_path):
        os.makedirs(solution_path)

    if file_type == 'cpp' or file_type == 'c':
        solution_filename = problem.stat['title_slug'] + '.' + file_type
        # Process the problem description
        description_text_list = textwrap.wrap(problem.stat['description'], width=70)
        description_text_formatted_list = []
        for line in description_text_list:
            description_text_formatted_list.append(" *\t\t" + line)
        description_text = '\n' + '\n'.join(description_text_formatted_list)
        problem.set_value('description', description_text)

        with open(solution_path + solution_filename, 'w') as f:
            f.write('/**\n')
            f.write(' * @file: ' + solution_filename + '\n')
            f.write(' * @problem: ' + str(problem.stat['id']) + '. ' + problem.stat['title'] + '\n')
            f.write(' * @url: ' + problem.stat['url'] + '\n')
            f.write(' * @description: ' + problem.stat['description'] + '\n')
            f.write(' * @author: ' + author_name + '\n')
            f.write(' * @date: ' + date + '\n')
            f.write(' */' + '\n')
    elif file_type == 'py':
        solution_filename = problem.stat['title_slug'].replace('-', '_') + '.' + file_type
        # Process the problem description
        description_text_list = textwrap.wrap(problem.stat['description'], width=70)
        description_text_formatted_list = []
        for line in description_text_list:
            description_text_formatted_list.append("#\t\t" + line)
        description_text = '\n' + '\n'.join(description_text_formatted_list)
        problem.set_value('description', description_text)

        with open(solution_path + solution_filename, 'w') as f:
            f.write('# @file: ' + solution_filename + '\n')
            f.write('# @problem: ' + str(problem.stat['id']) + '. ' + problem.stat['title'] + '\n')
            f.write('# @url: ' + problem.stat['url'] + '\n')
            f.write('# @description: ' + problem.stat['description'] + '\n')
            f.write('# @author: ' + author_name + '\n')
            f.write('# @date: ' + date + '\n')
    else:
        exit('==> ERROR: Unsupported source file type: {}'.format(file_type))


################## Prepare a new solution for LeetCode problem ##################
if not os.path.isfile(problems_list_json_filename):
    print('==> Problems list json file does not exist. Start downloading...')
    get_problems_list_json_file(problems_list_json_filename)
    print('==> Problems list json file has been downloaded.')
else:
    if args.update:
        print('==> Updating problems list json file...')
        get_problems_list_json_file(problems_list_json_filename)
        print('==> Problems list json file has been updated.')

if args.id >= 1:
    problem = Problem(args.id)
    problem.get_stat(problems_list_json_filename)
    if args.lang == 'c' or args.lang == 'C':
        create_new_solution(problem, solution_base_path, author_name, date, 'c')
    elif args.lang == 'c++' or args.lang == 'C++' or args.lang == 'cpp' or args.lang == 'cxx':
        create_new_solution(problem, solution_base_path, author_name, date, 'cpp')
    elif args.lang == 'python' or args.lang == 'Python' or args.lang == 'py':
        create_new_solution(problem, solution_base_path, author_name, date, 'py')
    else:
        exit('==> ERROR: Unsupported programming language: {}'.format(args.lang))
    print("==> All is ready! Enjoy programming!")
else:
    exit('==> ERROR: Invalid problem id: {}'.format(args.id))
