#!/usr/bin/env python3
"""
llm_augment.py — Augments Semgrep output with LLM analysis

Usage: python llm_augment.py --input results.json --output aug.json
"""
import json
import argparse


def augment_findings(input_path, output_path):
    with open(input_path) as f:
        findings = json.load(f)

    augmented = []
    for finding in findings:
        # In production: call LLM API to analyze each finding
        entry = {
            'file': finding.get('location', {}).get('file', ''),
            'line': finding.get('location', {}).get('line', 0),
            'check_id': finding.get('check_id', ''),
            'message': finding.get('extra', {}).get('message', ''),
            'llm_analysis': 'PENDING_LLM_ANALYSIS',
        }
        augmented.append(entry)

    with open(output_path, 'w') as f:
        json.dump(augmented, f, indent=2)

    print(f"Augmented {len(augmented)} findings -> {output_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', required=True)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    augment_findings(args.input, args.output)
