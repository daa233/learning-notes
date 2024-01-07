# Prepare a new solution for LeetCode problem
# This script is inspired by Hao Chen's shell scripts
# (https://github.com/haoel/leetcode/tree/master/scripts) and based on Ma Xiaoyang's Python scripts
# (https://github.com/xapcloud/Code-Grab-from-Leetcode)


from __future__ import print_function
import requests
import json
from bs4 import BeautifulSoup as bs
from loguru import logger
import textwrap
import os
import datetime
import argparse

lang_map_dict = {
    # C
    "c": "c",
    "C": "c",
    # C++
    "cpp": "cpp",
    "c++": "cpp",
    "C++": "cpp",
    "cxx": "cpp",
    # Python
    "py": "python",
    "python": "python",
    "Python": "python",
    # Python3
    "py3": "python3",
    "python3": "python3",
    "Python3": "python3",
    # Rust
    "rs": "rust",
    "rust": "rust",
    "Rust": "rust",
}

lang_info_dict = {
    "c": {"name": "c", "file_ext": "c", "comment_mark": "*"},
    "cpp": {"name": "cpp", "file_ext": "cpp", "comment_mark": "*"},
    "python": {"name": "python", "file_ext": "py", "comment_mark": "#"},
    "python3": {"name": "python3", "file_ext": "py", "comment_mark": "#"},
    "rust": {"name": "rust", "file_ext": "rs", "comment_mark": "//"},
}


def get_lang_and_file_ext(lang_str):
    if lang_str in lang_map_dict.keys():
        lang_slug = lang_map_dict[lang_str]
        return lang_info_dict[lang_slug]
    else:
        raise ValueError("Unsupported programming language: {}".format(lang_str))


class Solution(object):
    def __init__(self, id, lang, urls, author, date, translated=False):
        self.id = id  # the frontend question id, used to query the problem
        self.title = None
        self.title_slug = None
        self.description = None
        self.paid_only = None
        self.lang_info = get_lang_and_file_ext(lang)
        self.code = None
        self.filename = None
        self.urls = urls
        self.problem_url = None
        self.problem_json = None
        self.author = author
        self.date = date
        self.use_translated = translated

    def get_stat(self, problems_list_json_filename):
        """
        Find the problem's slug in the problems list json file, according to the problem id.
        Get the problem statistics according to the problem title.
        """
        # Load problems list and convert it to dictionary
        with open(problems_list_json_filename, "rb") as f:
            problems_list_str = f.read().decode()
            data_json = json.loads(problems_list_str)
            # Get the problems list
            problems_list = data_json["stat_status_pairs"]

        # Traverse the problems list and get the id-th problem
        found_flag = False
        for problem_item in problems_list:
            question_id = problem_item["stat"]["frontend_question_id"]
            if question_id == self.id:
                found_flag = True
                self.title_slug = problem_item["stat"]["question__title_slug"]
                self.title = problem_item["stat"]["question__title"]
                self.problem_url = self.urls["problem_base"] + self.title_slug
                self.paid_only = problem_item["paid_only"]

        if found_flag:
            if self.paid_only:
                raise PermissionError("Problem {} is paid only.".format(self.id))

            print("==> Found problem  {}. {}".format(self.id, self.title))

            try:
                # Send requests and get the specific problem description
                self.problem_json = post_to_get_problem_description(
                    self.urls, self.title_slug
                )

                switch_to_chinese_flag = (
                    "switch to Chinese"
                    in self.problem_json["data"]["question"]["content"]
                )

                if self.use_translated or switch_to_chinese_flag:
                    problem_desc_raw = self.problem_json["data"]["question"][
                        "translatedContent"
                    ]
                    self.title = self.problem_json["data"]["question"][
                        "translatedTitle"
                    ]
                else:
                    problem_desc_raw = self.problem_json["data"]["question"]["content"]
                problem_desc_bs = bs(problem_desc_raw, "html.parser")
                problem_desc_text = bs.get_text(problem_desc_bs)
                self.description = problem_desc_text
                code_json_all = self.problem_json["data"]["question"]["codeSnippets"]
                for code_json in code_json_all:
                    if code_json["langSlug"] == self.lang_info["name"]:
                        self.code = code_json["code"]
                        break

            except (
                requests.exceptions.ReadTimeout,
                requests.exceptions.ConnectTimeout,
            ):
                raise TimeoutError("Time out!")
        else:
            raise LookupError("Unable to find problem {}".format(self.id))

    def create(self, path="./", name=""):
        """
        According to the problem id, get the problem contents and write them to the solution
        file with specific type.
        """
        solution_filepath = self._prepare_filepath(path, name=name)
        file_content = self._get_solution_file_content()
        with open(solution_filepath, "w") as f:
            f.writelines(file_content)
        print(
            "==> The solution file have been created at '{}'".format(solution_filepath)
        )
        print("==> All is ready! Enjoy programming!")

    def _prepare_filepath(self, path, name=""):
        dirname_prefix = str(self.id)

        chinese_to_english_replace_dict = {
            "剑指 Offer": "lcof",  # 剑指 Offer
            "剑指 Offer II": "lcof-ii",  # 剑指 Offer II
            "面试题": "lcci",  # 程序员面试金典
        }

        if not dirname_prefix.isascii():
            for key, val in chinese_to_english_replace_dict.items():
                if dirname_prefix.startswith(key):
                    dirname_prefix = dirname_prefix.replace(key, val)
                # remove the "lcof/lcci" suffix
                if self.title_slug.endswith(val):
                    self.title_slug = self.title_slug.replace("-" + val, "")

        assert (
            dirname_prefix.isascii()
        ), "the dirname_prefix {} contains non-ASCII characters!"

        if not name:
            filename = self.title_slug
        else:
            filename = name

        dirname = "-".join([dirname_prefix, filename])

        dirname = dirname.replace(" - ", "-").replace("- ", "-").replace(" -", "-")
        dirname = dirname.replace(" ", "-").replace("_", "-").lower()
        filename = filename.replace(" ", "_").replace("-", "_").lower()

        solution_path = os.path.join(path, dirname)

        if self.lang_info["name"] in lang_info_dict:
            self.filename = ".".join([filename, self.lang_info["file_ext"]])
        else:
            raise NotImplementedError(
                "Unsupported source file type: {}".format(self.lang_info["file_ext"])
            )
        solution_file = os.path.join(solution_path, self.filename)

        if not os.path.exists(solution_path):
            os.makedirs(solution_path)
        if os.path.exists(solution_file):
            raise FileExistsError(
                "A solution file '{}' already exists. Nothing changed.".format(
                    solution_file
                )
            )

        return solution_file

    def _format_description(self, desc_text, comment_mark):
        sec_text_list = desc_text.split("\n\n")
        new_sec_text_list = []
        for sec_text in sec_text_list:
            subsec_text_list = sec_text.split("\n")
            subsec_text_list = [
                textwrap.wrap(text, width=70) for text in subsec_text_list
            ]
            new_subsec_text_list = []
            for subsec_text in subsec_text_list:
                if isinstance(subsec_text, list):
                    for item in subsec_text:
                        new_subsec_text_list.append(comment_mark + " " + item)
                else:
                    new_subsec_text_list.append(comment_mark + " " + subsec_text)
            if len(new_subsec_text_list) > 0:
                new_sec_text_list.append("\n".join(new_subsec_text_list))
        desc_text = ("\n" + comment_mark + "\n").join(new_sec_text_list)
        return desc_text

    def _process_file_head(self):
        head_comment = []
        # Format the description
        comment_mark = self.lang_info["comment_mark"]
        self.description = self._format_description(self.description, comment_mark)
        # Prepare the head comments of the file
        head_comment.append(
            comment_mark + " @problem: " + str(self.id) + ". " + self.title + "\n"
        )
        head_comment.append(comment_mark + " @file: " + self.filename + "\n")
        head_comment.append(comment_mark + " @url: " + self.problem_url + "\n")
        head_comment.append(comment_mark + " @description: \n")
        head_comment.append(comment_mark + "\n")
        head_comment.append(self.description + "\n")
        head_comment.append(comment_mark + "\n")
        head_comment.append(comment_mark + " @author: " + self.author + "\n")
        head_comment.append(comment_mark + " @date: " + self.date + "\n")
        return head_comment

    def _get_solution_file_content(self):
        file_content = []
        main_code_body = []
        lang = self.lang_info["name"]
        if lang in ["c", "cpp"]:
            head_comment = self._process_file_head()
            file_content.append("/** \n")
            file_content += head_comment
            file_content.append(" */\n\n")
            if lang == "c":
                file_content.append("#include <stdio.h>\n\n")
            elif lang == "cpp":
                file_content.append("#include <iostream>\n\n")
                file_content.append("using namespace std;\n\n")
            main_code_body.append(
                "int main (int argc, char *argv[])\n{\n    return 0;\n}"
            )
        elif lang in ["python", "python3"]:
            head_content = self._process_file_head()
            file_content += head_content
            file_content.append("\n")
        elif lang in ["rust"]:
            head_content = self._process_file_head()
            file_content += head_content
            file_content.append("\n")
        else:
            raise NotImplementedError(
                "Unsupported source file type: {}".format(self.lang_info["file_ext"])
            )
        file_content.append("\n")
        file_content.append(self.code)
        file_content.append("\n\n\n")
        file_content += main_code_body
        file_content.append("\n")
        return file_content


def get_problems_list_json_file(
    problems_list_json_filename, problems_list_base_url, category_slug
):
    """
    Get the problems list json file.
    If problems list json file does not exist, send requests, get responses and save it.
    """
    try:
        r = requests.get(url=problems_list_base_url + category_slug)
        data = json.loads(r.text)
        # Write to json file 'problems_list.json'
        with open(problems_list_json_filename, "w") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)
        r.close()
    except (
        requests.exceptions.ReadTimeout,
        requests.exceptions.ConnectTimeout,
    ):
        raise TimeoutError("Time out!")


def post_to_get_problem_description(urls, problem_title_slug):
    # payload = "{\"operationName\":\"questionData\",\"variables\":{\"titleSlug\":\"" + problem_title_slug + \
    #     "\"},\"query\":\"query questionData($titleSlug: String!) {\\n  question(titleSlug: $titleSlug) {\\n    questionId\\n    questionFrontendId\\n    boundTopicId\\n    title\\n    titleSlug\\n    content\\n    translatedTitle\\n    translatedContent\\n    isPaidOnly\\n    difficulty\\n    likes\\n    dislikes\\n    isLiked\\n    similarQuestions\\n    contributors {\\n      username\\n      profileUrl\\n      avatarUrl\\n      __typename\\n    }\\n    langToValidPlayground\\n    topicTags {\\n      name\\n      slug\\n      translatedName\\n      __typename\\n    }\\n    companyTagStats\\n    codeSnippets {\\n      lang\\n      langSlug\\n      code\\n      __typename\\n    }\\n    stats\\n    hints\\n    solution {\\n      id\\n      canSeeDetail\\n      __typename\\n    }\\n    status\\n    sampleTestCase\\n    metaData\\n    judgerAvailable\\n    judgeType\\n    mysqlSchemas\\n    enableRunCode\\n    enableTestMode\\n    envInfo\\n    __typename\\n  }\\n}\\n\"}"

    # a shorter payload
    payload = (
        '{\n    "operationName": "questionData",\n    "variables": {\n        "titleSlug": "'
        + problem_title_slug
        + '"\n    },\n    "query": "query questionData($titleSlug: String!) {\\n  question(titleSlug: $titleSlug) {\\n    questionId\\n    questionFrontendId\\n    boundTopicId\\n    title\\n    titleSlug\\n    content\\n    translatedTitle\\n    translatedContent\\n    isPaidOnly\\n    difficulty\\n    similarQuestions\\n    codeSnippets {\\n      lang\\n      langSlug\\n      code\\n    }\\n    sampleTestCase\\n}\\n}\\n"\n}'
    )

    headers = {
        "accept": "*/*",
        "referer": urls["problem_post"] + problem_title_slug + "/description /",
        "origin": urls["origin"],
        "user-agent": "mozilla/5.0",
        "content-type": "application/json",
        "cache-control": "no-cache",
    }

    problem_response = requests.request(
        "post", urls["problem_post"], data=payload, headers=headers
    )

    if problem_response.status_code == 200:
        problem_json = json.loads(problem_response.text)
        problem_response.close()
        return problem_json
    else:
        msg = f"error: {problem_response.text}"
        logger.error(msg)
        raise ValueError(msg)


def main():
    parser = argparse.ArgumentParser(
        description="Prepare a new solution for LeetCode problem"
    )

    parser.add_argument(
        "-i",
        "--id",
        dest="id",
        default="",
        type=str,
        help="specify the problem id",
    )
    parser.add_argument(
        "-u" "--update",
        "--update-list",
        dest="update",
        action="store_true",
        help="update the problems list json file",
    )
    parser.add_argument(
        "-l",
        "--lang",
        "--language",
        dest="lang",
        default="c++",
        type=str,
        help="language option: c, c++, python, rust",
    )
    parser.add_argument(
        "-p",
        "--path",
        default="./",
        type=str,
        help="the parent directory to create the solution",
    )
    parser.add_argument(
        "-n",
        "--name",
        default="",
        type=str,
        help="use the specified solution name",
    )
    parser.add_argument(
        "-t",
        "--translated",
        action="store_true",
        help="use the translated title and content",
    )

    # origin_url = 'https://leetcode.com/'
    # origin_url = "https://leetcode-cn.com/"
    origin_url = "https://leetcode.cn/"
    urls = {
        "origin": origin_url,
        "problem_list": origin_url + "api/problems/",
        "problem_base": origin_url + "problems/",
        "problem_post": origin_url + "graphql/",
    }

    # option for category_slug: [all, algorithms, database, shell, concurrency, lcci, lcof]
    category_slug = "all"
    problems_list_json_filename = "problems_list.json"
    author_name = "Du Ang"
    date = datetime.date.today().strftime("%b %d, %Y")

    # Parse the arguments
    args = parser.parse_args()
    if not os.path.isfile(problems_list_json_filename):
        print("==> Problems list json file does not exist. Start downloading...")
        get_problems_list_json_file(
            problems_list_json_filename, urls["problem_list"], category_slug
        )
        print("==> Problems list json file has been downloaded.")
    else:
        if args.update:
            print("==> Updating problems list json file...")
            get_problems_list_json_file(
                problems_list_json_filename, urls["problem_list"], category_slug
            )
            print("==> Problems list json file has been updated.")

    if args.id:
        solution = Solution(
            args.id, args.lang, urls, author_name, date, args.translated
        )
        solution.get_stat(problems_list_json_filename)
        # Prepare a new solution for LeetCode problem
        solution.create(args.path, args.name)
    else:
        print(args)
        raise ValueError("Invalid problem id: {}".format(args.id))


if __name__ == "__main__":
    main()
