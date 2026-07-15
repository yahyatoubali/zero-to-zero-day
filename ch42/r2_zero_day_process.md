# R-2: Zero-Day Discovery
#
# Methodology for finding a real zero-day vulnerability:
#
# 1. Target Selection
#    - Pick a bug bounty program with clear scope
#    - Choose a target with sufficient complexity
#    - Prefer targets with good disclosure track records
#
# 2. Reconnaissance (Week 1-2)
#    - Understand the architecture
#    - Map the attack surface
#    - Read past CVEs and fix patches
#    - Identify high-risk areas (parsers, network-facing code)
#
# 3. Fuzzing Campaign (Week 3-6)
#    - Write targeted harnesses
#    - Run AFL++/libFuzzer with AddressSanitizer
#    - Triage and deduplicate crashes
#    - Minimize crashing inputs
#
# 4. Manual Analysis (Week 7-8)
#    - Reverse engineer crash paths
#    - Determine exploitability
#    - Build proof of concept
#
# 5. Disclosure
#    - Write clear, professional advisory
#    - Submit through proper channels
#    - Coordinate fix timeline
#
# Success criteria: CVE assignment + bounty + fix merged upstream.
