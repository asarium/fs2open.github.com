#!/usr/bin/env python3

import argparse
import os
import hashlib
import json

from os import path


def get_hash(file_path):
    digest = hashlib.sha256()
    with open(file_path, "rb") as f:
        while True:
            data = f.read(65536)  # Read 64k parts of the file
            if not data:
                break

            digest.update(data)

    return digest.hexdigest()


parser = argparse.ArgumentParser(description="Generate a performance graph")
parser.add_argument("install_dir")
parser.add_argument("input_file")
args = parser.parse_args()

file_dir = args.install_dir
input_file = args.input_file

hash_list = []

print("Computing hash values...")
for root, dirs, files in os.walk(file_dir):
    for file in files:
        file_path = path.join(root, file)

        relative = path.relpath(file_path, file_dir)
        print("Computing hash for {}...".format(relative))
        hash_list.append({
            "file": relative,
            "hash": get_hash(file_path)
        })

with open(input_file, "r") as f:
    base_data = json.load(f)

hash_obj = {
    "algorithm": "sha-256",
    "hashes": hash_list
}
base_data["hash"] = hash_obj

with open(path.join(file_dir, "metadata.json"), "w") as f:
    print("Writing metadata...")
    base_data = json.dump(base_data, f)
