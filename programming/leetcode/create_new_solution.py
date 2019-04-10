# Prepare a new solution for LeetCode problem
# This script is inspired by Hao Chen's shell scripts
# (https://github.com/haoel/leetcode/tree/master/scripts) and based on Ma Xiaoyang's Python scripts
# (https://github.com/xapcloud/Code-Grab-from-Leetcode)


from __future__ import print_function
import requests
import json
from bs4 import BeautifulSoup as bs
import textwrap
import os
import datetime
import argparse


class Solution(object):
    def __init__(self, id, lang, urls, author, date):
        self.id = id
        self.title = None
        self.tile_slug = None
        self.description = None
        self.paid_only = None
        self.lang = lang
        self.code = None
        self.filename = None
        self.urls = urls
        self.problem_url = None
        self.problem_json = None
        self.author = author
        self.date = date

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

        # Traverse the problems list and get the id-th problem
        found_flag = False
        for problem_item in problems_list:
            if problem_item['stat']['frontend_question_id'] == self.id:
                found_flag = True
                self.title_slug = problem_item['stat']['question__title_slug']
                self.title = problem_item['stat']['question__title']
                self.problem_url = self.urls['problem_base'] + self.title_slug
                self.paid_only = problem_item['paid_only']

        if found_flag:
            if self.paid_only:
                exit('==> ERROR: Problem {} is paid only.'.format(
                    self.id))

            print('==> Found problem  {}. {}'.format(
                self.id, self.title))

            try:
                # Send requests and get the specific problem description
                self.problem_json = post_to_get_problem_description(
                    self.urls, self.title_slug)
                problem_desc_raw = self.problem_json['data']['question']['content']
                problem_desc_bs = bs(problem_desc_raw, 'html.parser')
                problem_desc_text = bs.get_text(problem_desc_bs)
                self.description = problem_desc_text
                code_json_all = self.problem_json['data']['question']['codeSnippets']
                for code_json in code_json_all:
                    if code_json['langSlug'] == self.lang:
                        self.code = code_json['code']
                        break

            except (requests.exceptions.ReadTimeout, requests.exceptions.ConnectTimeout):
                exit('==> ERROR: Time out!')
        else:
            exit('==> ERROR: Unable to find problem {}'.format(args.id))


def get_problems_list_json_file(problems_list_json_filename, problems_list_base_url, category_slug):
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
    except (requests.exceptions.ReadTimeout, requests.exceptions.ConnectTimeout):
        exit('==> ERROR: Time out!')


def post_to_get_problem_description(urls, problem_title_slug):
    # payload = "{\"operationName\":\"questionData\",\"variables\":{\"titleSlug\":\"" + problem_title_slug + \
    #     "\"},\"query\":\"query questionData($titleSlug: String!) {\\n  question(titleSlug: $titleSlug) {\\n    questionId\\n    questionFrontendId\\n    boundTopicId\\n    title\\n    titleSlug\\n    content\\n    translatedTitle\\n    translatedContent\\n    isPaidOnly\\n    difficulty\\n    likes\\n    dislikes\\n    isLiked\\n    similarQuestions\\n    contributors {\\n      username\\n      profileUrl\\n      avatarUrl\\n      __typename\\n    }\\n    langToValidPlayground\\n    topicTags {\\n      name\\n      slug\\n      translatedName\\n      __typename\\n    }\\n    companyTagStats\\n    codeSnippets {\\n      lang\\n      langSlug\\n      code\\n      __typename\\n    }\\n    stats\\n    hints\\n    solution {\\n      id\\n      canSeeDetail\\n      __typename\\n    }\\n    status\\n    sampleTestCase\\n    metaData\\n    judgerAvailable\\n    judgeType\\n    mysqlSchemas\\n    enableRunCode\\n    enableTestMode\\n    envInfo\\n    __typename\\n  }\\n}\\n\"}"

    # a shorter payload
    payload = "{\n    \"operationName\": \"questionData\",\n    \"variables\": {\n        \"titleSlug\": \"" + problem_title_slug + \
        "\"\n    },\n    \"query\": \"query questionData($titleSlug: String!) {\\n  question(titleSlug: $titleSlug) {\\n    questionId\\n    questionFrontendId\\n    boundTopicId\\n    title\\n    titleSlug\\n    content\\n    translatedTitle\\n    translatedContent\\n    isPaidOnly\\n    difficulty\\n    similarQuestions\\n    codeSnippets {\\n      lang\\n      langSlug\\n      code\\n    }\\n    sampleTestCase\\n}\\n}\\n\"\n}"

    headers = {
        'accept': "*/*",
        'Referer': urls['problem_post'] + problem_title_slug + "/description /",
        'Origin': urls['origin'],
        'User-Agent': "Mozilla/5.0",
        'content-type': "application/json",
        'cache-control': "no-cache",
    }

    problem_response = requests.request(
        "POST", urls['problem_post'], data=payload, headers=headers)
    problem_json = json.loads(problem_response.text)
    problem_response.close()
    return problem_json


def format_description(desc_text, comment_mark):
    sec_text_list = desc_text.split('\n\n')
    new_sec_text_list = []
    for sec_text in sec_text_list:
        subsec_text_list = sec_text.split('\n')
        subsec_text_list = [textwrap.wrap(text, width=70)
                            for text in subsec_text_list]
        new_subsec_text_list = []
        for subsec_text in subsec_text_list:
            if isinstance(subsec_text, list):
                for item in subsec_text:
                    new_subsec_text_list.append(comment_mark + item)
            else:
                new_subsec_text_list.append(comment_mark + subsec_text)
        if len(new_subsec_text_list) > 0:
            new_sec_text_list.append('\n'.join(new_subsec_text_list))
    desc_text = ('\n' + comment_mark + '\n').join(new_sec_text_list)
    return desc_text


def process_file_head(solution, comment_mark):
    head_comment = []
    # Format the description
    solution.description = format_description(
        solution.description, comment_mark)
    # Prepare the head comments of the file
    head_comment.append(comment_mark + '@problem: '
                        + str(solution.id) + '. '
                        + solution.title + '\n')
    head_comment.append(comment_mark + '@file: ' +
                        solution.filename + '\n')
    head_comment.append(comment_mark + '@url: ' + solution.problem_url + '\n')
    head_comment.append(comment_mark + '@description: \n')
    head_comment.append(comment_mark + '\n')
    head_comment.append(solution.description + '\n')
    head_comment.append(comment_mark + '\n')
    head_comment.append(comment_mark + '@author: ' +
                        solution.author + '\n')
    head_comment.append(comment_mark + '@date: ' + solution.date + '\n')
    return head_comment


def process_solution_file(solution):
    file_content = []
    main_code_body = []
    file_type = solution.lang
    if file_type == 'cpp' or file_type == 'c':
        solution.filename = solution.title_slug + '.' + file_type
        comment_mark = ' * '
        head_comment = process_file_head(solution, comment_mark)
        file_content.append('/** \n')
        file_content += head_comment
        file_content.append(' */\n\n')
        if file_type == 'c':
            file_content.append('#include <stdio.h>\n\n')
        elif file_type == 'cpp':
            file_content.append('#include <iostream>\n\n')
            file_content.append('using namespace std;\n\n')
        main_code_body.append(
            'int main (int argc, char *argv[])\n{\n    return 0;\n}')
    elif file_type == 'python' or file_type == 'python3':
        solution.filename = solution.title_slug.replace('-', '_') + '.py'
        comment_mark = '# '
        head_content = process_file_head(solution, comment_mark)
        file_content += head_content
        file_content.append('\n')
    else:
        exit('==> ERROR: Unsupported source file type: {}'.format(file_type))
    file_content.append('\n')
    file_content.append(solution.code)
    file_content.append('\n\n\n')
    file_content += main_code_body
    file_content.append('\n')
    return file_content


def create_new_solution(solution, solution_base_path):
    '''
    According to the problem id, get the problem contents and write them to the solution
    file with specific type.
    '''
    solution_path = solution_base_path + \
        str(solution.id) + '-' + solution.title_slug
    if not os.path.isdir(solution_path):
        os.makedirs(solution_path)
    file_content = process_solution_file(solution)
    solution_file = os.path.join(solution_path, solution.filename)
    if os.path.exists(solution_file):
        exit("==> A solution file \'{}\' already exists. Nothing changed.".format(
            solution_file))
    else:
        with open(solution_file, 'w') as f:
            f.writelines(file_content)
        print("==> The solution file have been created at \'{}\'".format(solution_file))
        print("==> All is ready! Enjoy programming!")


def main():
    parser = argparse.ArgumentParser(
        description='Prepare a new solution for LeetCode problem')

    parser.add_argument('--id', dest='id', default='0', type=int,
                        help='specify the problem id')
    parser.add_argument('--update_list', '--update', dest='update', action='store_true',
                        help='update the problems list json file')
    parser.add_argument('--lang', '--language', dest='lang', default='c++', type=str,
                        help='language option: c, c++, python')

    # origin_url = 'https://leetcode.com/'
    origin_url = 'https://leetcode-cn.com/'
    urls = {
        'origin': origin_url,
        'problem_list': origin_url + 'api/problems/',
        'problem_base': origin_url + 'problems/',
        'problem_post': origin_url + 'graphql/'
    }

    category_slug = 'all'   # option: all, algorithms, database, shell
    problems_list_json_filename = 'problems_list.json'
    solution_base_path = './'
    author_name = 'Du Ang'
    date = datetime.date.today().strftime('%b %d, %Y')

    lang_slug_dict = {
        'c': 'c',
        'cpp': 'cpp',
        'python': 'python',
        'python3': 'python3'
    }

    lang_map_dict = {
        # C
        'c': lang_slug_dict['c'],
        'C': lang_slug_dict['c'],
        # C++
        'cpp': lang_slug_dict['cpp'],
        'c++': lang_slug_dict['cpp'],
        'C++': lang_slug_dict['cpp'],
        'cxx': lang_slug_dict['cpp'],
        # Python
        'py': lang_slug_dict['python'],
        'python': lang_slug_dict['python'],
        'Python': lang_slug_dict['python'],
        # Python3
        'py3': lang_slug_dict['python3'],
        'python3': lang_slug_dict['python3'],
        'Python3': lang_slug_dict['python3'],
    }

    # Parse the arguments
    args = parser.parse_args()
    if not os.path.isfile(problems_list_json_filename):
        print('==> Problems list json file does not exist. Start downloading...')
        get_problems_list_json_file(
            problems_list_json_filename, urls['problem_list'], category_slug)
        print('==> Problems list json file has been downloaded.')
    else:
        if args.update:
            print('==> Updating problems list json file...')
            get_problems_list_json_file(
                problems_list_json_filename, urls['problem_list'], category_slug)
            print('==> Problems list json file has been updated.')

    if args.id >= 1:
        if args.lang in lang_map_dict.keys():
            lang_slug = lang_map_dict[args.lang]
        else:
            exit('==> ERROR: Unsupported programming language: {}'.format(args.lang))
        solution = Solution(args.id, lang_slug, urls, author_name, date)
        solution.get_stat(problems_list_json_filename)
        # Prepare a new solution for LeetCode problem
        create_new_solution(solution, solution_base_path)

    else:
        exit('==> ERROR: Invalid problem id: {}'.format(args.id))


if __name__ == '__main__':
    main()
