## Codecov with C++ and GitHub Actions
<br>

![alt text](images/1.png?raw=true "sortie de code")

<div class="col-md-8">    
                
<p>Tests are an important component of software development: they help prevent bugs and can act as documentation. One of the best ways to ensure your code quality stays high over time is to monitor your test coverage, through a measure known as code coverage. Monitoring code coverage is essential to maintaining code quality, and there are many tools out there that can assist with this.</p>
<p><a href="https://github.com/OpenCppCoverage/OpenCppCoverage">OpenCppCoverage</a>&nbsp;is an open-source C++ code coverage tool for Windows that can generate coverage reports locally, and then leverage Codecov GitHub Actions to integrate coverage reports in your CI pipeline.</p>
<p>In this tutorial, you will learn the basics of OpenCppCoverage and how to integrate it into your CI pipeline. If you’d like to skip ahead to the full code for the demo, it is available&nbsp;<a href="https://github.com/Qannaf/Codecov_GitHubActions_CPlusPlus.git">here</a>.</p>
<h2 id="running-tests-and-coverage-locally">Running Tests and Coverage Locally</h2>
<p>To follow this tutorial, you need Windows Vista or higher and Microsoft Visual Studio 2008 or higher. You can clone the demo repository with the following command:</p>
<pre><code class="lang-Git">git <span class="hljs-keyword">clone</span> <span class="hljs-title">https</span>://github.com/Qannaf/Codecov_GitHubActions_CPlusPlus.git
</code></pre>
<p>Alternatively, you can proceed with the step-by-step instructions below.</p>
<h3 id="1-creating-a-library">1. Creating a Library</h3>
<p>First, you will create a static library project from Visual Studio. The library will house computations below that can be performed with bit operations.</p>
<pre><code class="lang-C++ hljs"><span class="hljs-comment"><span class="hljs-comment">// HelloCov.h</span></span>
<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">bool</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">is_power_of_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span></span>;
<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">int</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">multiply_by_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span></span>;
<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">int</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">divide_by_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span></span>;
</code></pre>
<pre><code class="lang-C++ hljs"><span class="hljs-comment"><span class="hljs-comment">//HelloCov.cpp</span></span>
<span class="hljs-meta"><span class="hljs-meta">#</span><span class="hljs-meta-keyword"><span class="hljs-meta"><span class="hljs-meta-keyword">include</span></span></span><span class="hljs-meta"> </span><span class="hljs-meta-string"><span class="hljs-meta"><span class="hljs-meta-string">"HelloCov.h"</span></span></span></span>

<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">bool</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">is_power_of_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span><span class="hljs-function">
</span></span>{
    <span class="hljs-keyword"><span class="hljs-keyword">if</span></span> (n &lt; <span class="hljs-number"><span class="hljs-number">0</span></span>)
        <span class="hljs-keyword"><span class="hljs-keyword">return</span></span> <span class="hljs-literal"><span class="hljs-literal">false</span></span>;

    <span class="hljs-keyword"><span class="hljs-keyword">return</span></span> (n &amp; (n - <span class="hljs-number"><span class="hljs-number">1</span></span>)) == <span class="hljs-number"><span class="hljs-number">0</span></span>;
}

<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">int</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">multiply_by_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span><span class="hljs-function">
</span></span>{
    <span class="hljs-keyword"><span class="hljs-keyword">return</span></span> n &lt;&lt; <span class="hljs-number"><span class="hljs-number">1</span></span>;
}

<span class="hljs-function"><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-keyword">int</span></span></span><span class="hljs-function"> </span><span class="hljs-title"><span class="hljs-function"><span class="hljs-title">divide_by_two</span></span></span><span class="hljs-params"><span class="hljs-function"><span class="hljs-params">(</span></span><span class="hljs-keyword"><span class="hljs-function"><span class="hljs-params"><span class="hljs-keyword">int</span></span></span></span><span class="hljs-function"><span class="hljs-params"> n)</span></span></span><span class="hljs-function">
</span></span>{
    <span class="hljs-keyword"><span class="hljs-keyword">return</span></span> n &gt;&gt; <span class="hljs-number"><span class="hljs-number">1</span></span>;
}
</code></pre>
<p>Ensure the library compiles successfully, then proceed to add tests.</p>
<h3 id="2-add-tests">2. Add Tests</h3>
<p>In the same solution, add a&nbsp;<code>Native Unit Test Project</code>&nbsp;with reference to the&nbsp;<code>HelloCov</code>&nbsp;library. In a source file, add one test method for each function as follows:</p>
<pre><code class="lang-C++ hljs"><span class="hljs-meta"><span class="hljs-meta">#</span><span class="hljs-meta-keyword"><span class="hljs-meta"><span class="hljs-meta-keyword">include</span></span></span><span class="hljs-meta"> </span><span class="hljs-meta-string"><span class="hljs-meta"><span class="hljs-meta-string">"CppUnitTest.h"</span></span></span></span>
<span class="hljs-meta"><span class="hljs-meta">#</span><span class="hljs-meta-keyword"><span class="hljs-meta"><span class="hljs-meta-keyword">include</span></span></span><span class="hljs-meta"> </span><span class="hljs-meta-string"><span class="hljs-meta"><span class="hljs-meta-string">"../HelloCov/HelloCov.h"</span></span></span></span>

<span class="hljs-keyword"><span class="hljs-keyword">using</span></span> <span class="hljs-keyword"><span class="hljs-keyword">namespace</span></span> Microsoft::VisualStudio::CppUnitTestFramework;

<span class="hljs-keyword"><span class="hljs-keyword">namespace</span></span> HelloCovTest
{
  TEST_CLASS(Test1)
  {
  <span class="hljs-keyword"><span class="hljs-keyword">public</span></span>:

    TEST_METHOD(IsPowerOfTwo)
    {
      Assert::IsTrue(is_power_of_two(<span class="hljs-number"><span class="hljs-number">8</span></span>));
    }

    TEST_METHOD(MultiplyByTwo)
    {
      Assert::AreEqual(<span class="hljs-number"><span class="hljs-number">14</span></span>, multiply_by_two(<span class="hljs-number"><span class="hljs-number">7</span></span>));
    }

    TEST_METHOD(DivideByTwo)
    {
      Assert::AreEqual(<span class="hljs-number"><span class="hljs-number">-4</span></span>, divide_by_two(<span class="hljs-number"><span class="hljs-number">-7</span></span>));
    }
  };
}
</code></pre>
<p>Verify that all the tests pass.</p>
<h3 id="3-install-opencppcoverage">3. Install OpenCppCoverage</h3>
<p>There are two ways to install it—using&nbsp;<a href="https://chocolatey.org/">Chocolatey</a>:</p>
<pre><code class="lang-cmd hljs dos">choco <span class="hljs-keyword">install</span> opencppcoverage
</code></pre>
<p>Or using the interactive installer. Go to&nbsp;<a href="https://github.com/OpenCppCoverage/OpenCppCoverage/releases">releases</a>&nbsp;and download the latest release of the installer.</p>
<h3 id="4-generate-code-coverage-report">4. Generate Code Coverage Report</h3>
<p>From the root directory of the solution, run the following command:</p>
<pre><code class="lang-cmd hljs dos">OpenCppCoverage --sources HelloCov -- "C:<span class="hljs-symbol">\P</span>rogram Files (x86)<span class="hljs-symbol">\M</span>icrosoft Visual Studio<span class="hljs-symbol">\<span class="hljs-number">2</span></span><span class="hljs-number">019</span><span class="hljs-symbol">\C</span>ommunity<span class="hljs-symbol">\C</span>ommon7<span class="hljs-symbol">\I</span>DE<span class="hljs-symbol">\C</span>ommonExtensions<span class="hljs-symbol">\M</span>icrosoft<span class="hljs-symbol">\T</span>estWindow<span class="hljs-symbol">\v</span>stest.console.exe" debug/HelloTest.dll
</code></pre>
<p>The path of&nbsp;<code>vstest.console.exe</code>&nbsp;depends on your version of Visual Studio, so update it accordingly. The report will be generated in the folder&nbsp;<code>CodeCoverage-&lt;Timestamp&gt;</code>. You can view it by opening&nbsp;<code>index.html</code>&nbsp;in a browser. On navigating to the report for&nbsp;<code>HelloTest.dll</code>&nbsp;&gt;&nbsp;<code>HelloCov.cpp</code>, you will see the line coverage like below:</p>
<p><img src="images/qaeNYKL.png" alt="Capture of line coverage"></p>
<h2 id="configuring-github-actions">Configuring GitHub Actions</h2>
<p>Coverage reports are most useful when making changes to your code. In this section, you will integrate Codecov into your workflow so that you are able to view reports on pull requests or pushes to your repo.</p>
<h3 id="1-repo">1. Repo</h3>
<p>Create a public GitHub and push to it the solution above.</p>
<h3 id="2-sign-up-for-codecov">2. Sign Up for Codecov</h3>
<p>If you don’t already have an account, head over to&nbsp;<a href="https://about.codecov.io/">Codecov</a>&nbsp;and sign up with your GitHub account. Select the repo you will be integrating. This tutorial uses a public repo for simplicity but if your repo is private you will be provided a token. Alternatively, you can add a repo by navigating to&nbsp;<code>https://app.codecov.io/gh/&lt;gh-username&gt;/&lt;repo-name&gt;</code>.</p>
<h3 id="3-setup-github-actions">3. Setup GitHub Actions</h3>
<p><a href="https://github.com/features/actions">GitHub Actions</a>&nbsp;make it easy to automate software workflows. You’ll set up a workflow to essentially run OpenCppCoverage on a Windows machine, then upload the report to CodeCov. These actions are specified in a YAML file in the&nbsp;<code>.github/workflows</code>&nbsp;directory in your repo. Add the YAML file below to your workflows folder:</p>
<pre><code class="lang-yml hljs yaml"><span class="hljs-attr"><span class="hljs-attr">name:</span></span> <span class="hljs-string">Upload</span> <span class="hljs-string">CodeCov</span> <span class="hljs-string">Report</span>
<span class="hljs-attr"><span class="hljs-attr">on:</span></span> [<span class="hljs-string">push</span>, <span class="hljs-string">pull_request</span>]
<span class="hljs-attr"><span class="hljs-attr">jobs:</span></span>
<span class="hljs-attr">  <span class="hljs-attr">run:</span></span>
<span class="hljs-attr">    <span class="hljs-attr">runs-on:</span></span> <span class="hljs-string">windows-latest</span>
<span class="hljs-attr">    <span class="hljs-attr">name:</span></span> <span class="hljs-string">Build,</span> <span class="hljs-string">Test</span> <span class="hljs-string">,</span> <span class="hljs-string">Upload</span> <span class="hljs-string">Code</span> <span class="hljs-string">Coverage</span> <span class="hljs-string">Report</span>
<span class="hljs-attr">    <span class="hljs-attr">steps:</span></span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Checkout</span> <span class="hljs-string">code</span>
<span class="hljs-attr">        <span class="hljs-attr">uses:</span></span> <span class="hljs-string">actions/checkout@v2</span>
<span class="hljs-attr">        <span class="hljs-attr">with:</span></span>
<span class="hljs-attr">          <span class="hljs-attr">fetch-depth:</span></span> <span class="hljs-string">‘</span><span class="hljs-number"><span class="hljs-string">2</span></span><span class="hljs-string">’</span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">checkout_code</span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Setup</span> <span class="hljs-string">MSBuild</span> <span class="hljs-string">and</span> <span class="hljs-string">add</span> <span class="hljs-string">to</span> <span class="hljs-string">PATH</span>
<span class="hljs-attr">        <span class="hljs-attr">uses:</span></span> <span class="hljs-string">microsoft/setup-msbuild@v1</span><span class="hljs-number"><span class="hljs-string">.0</span></span><span class="hljs-number"><span class="hljs-string">.2</span></span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">setup_msbuild</span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Run</span> <span class="hljs-string">MSBuild</span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">run_msbuild</span>
<span class="hljs-attr">        <span class="hljs-attr">run:</span></span> <span class="hljs-string">msbuild</span> <span class="hljs-string">/p:Configuration=Debug</span> <span class="hljs-string">/p:Platform=x86</span> <span class="hljs-string">HelloCovDemo.sln</span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Setup</span> <span class="hljs-string">VSTest</span> <span class="hljs-string">and</span> <span class="hljs-string">add</span> <span class="hljs-string">to</span> <span class="hljs-string">PATH</span>
<span class="hljs-attr">        <span class="hljs-attr">uses:</span></span> <span class="hljs-string">darenm/Setup-VSTest@v1</span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">setup_vstest</span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Setup</span> <span class="hljs-string">OpenCppCoverage</span> <span class="hljs-string">and</span> <span class="hljs-string">add</span> <span class="hljs-string">to</span> <span class="hljs-string">PATh</span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">setup_opencppcoverage</span>
<span class="hljs-attr">        <span class="hljs-attr">run:</span></span> <span class="hljs-string"><span class="hljs-string">|
          choco install OpenCppCoverage -y
          echo "C:\Program Files\OpenCppCoverage" &gt;&gt; $env:GITHUB_PATH
</span></span><span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Generate</span> <span class="hljs-string">Report</span>
<span class="hljs-attr">        <span class="hljs-attr">id:</span></span> <span class="hljs-string">generate_test_report</span>
<span class="hljs-attr">        <span class="hljs-attr">shell:</span></span> <span class="hljs-string">cmd</span>
<span class="hljs-attr">        <span class="hljs-attr">run:</span></span> <span class="hljs-string">OpenCppCoverage.exe</span> <span class="hljs-string">--sources</span> <span class="hljs-string">HelloCov</span> <span class="hljs-string">--export_type</span> <span class="hljs-string">cobertura:HelloCov.xml</span> <span class="hljs-string">--</span> <span class="hljs-string"><span class="hljs-string">"vstest.console.exe"</span></span> <span class="hljs-string">Debug\HelloTest.dll</span>
<span class="hljs-attr">      <span class="hljs-bullet">-</span> <span class="hljs-attr">name:</span></span> <span class="hljs-string">Upload</span> <span class="hljs-string">Report</span> <span class="hljs-string">to</span> <span class="hljs-string">Codecov</span>
<span class="hljs-attr">        <span class="hljs-attr">uses:</span></span> <span class="hljs-string">codecov/codecov-action@v1</span><span class="hljs-number"><span class="hljs-string">.3</span></span><span class="hljs-number"><span class="hljs-string">.2</span></span>
<span class="hljs-attr">        <span class="hljs-attr">with:</span></span>
<span class="hljs-attr">          <span class="hljs-attr">files:</span></span> <span class="hljs-string">./HelloCov.xml</span>
<span class="hljs-attr">          <span class="hljs-attr">fail_ci_if_error:</span></span> <span class="hljs-literal"><span class="hljs-literal">true</span></span>
<span class="hljs-attr">          <span class="hljs-attr">functionalities:</span></span> <span class="hljs-string">fix</span>
</code></pre>
<p>The actions are described by their respective&nbsp;<code>name</code>&nbsp;properties. They mirror what we manually did to generate local reports i.e setup, build, test,k and coverage. Of importance are the last two actions that generate and upload the report. The&nbsp;<code>OpenCppCoverage</code>&nbsp;command is similar to the one used locally, and the&nbsp;<code>export_type</code>&nbsp;parameter is added to get the report in xml, one of the Codecov supported formats. The absolute path of vstest is not required since&nbsp;<code>setup_vstest</code>&nbsp;action added it to global PATH. When you push this change you can monitor the workflow from the Actions tab of the repo on GitHub.</p>
<h3 id="4-view-codecov-report">4. View Codecov Report</h3>
<p>If the workflow succeeds, at the end of logs for the upload action, there will be a link to the Codecov report like below:</p>
<p><img src="https://about.codecov.io/wp-content/uploads/2021/06/D2NdzXo.png" alt="report"></p>
<p>Navigate to the link for a detailed report including the conspicuous coverage percentage. Under the Files tab, you can view line-by-line coverage for each file.</p>
<p><img src="images/z1Yi7ZE.png" alt="linecoverage"></p>
<p>Under the Graphs tab, you can view graphical representations of your coverage, like the sunburst below:</p>
<p><img src="images/LcSojru.png" alt="Sunburst"></p>
<p><a href="https://docs.codecov.io/docs/graphs#sunburst">Sunburst graphs</a>&nbsp;enable you to navigate into project folders in order to discover files that lack coverage. The size of each slice is proportional to the number of coverage lines and the color indicates coverage. Click on a block to enter a folder and click the innermost circle to leave it.</p>
<h3 id="5-change-report">5. Change Report</h3>
<p>To view coverage reports as comments on pull requests, set up as follows:</p>
<ul>
<li>Add empty&nbsp;<code>codecov.yml</code>&nbsp;to the root of the repo.</li>
<li>Grant access to the&nbsp;<a href="https://github.com/marketplace/codecov">codecov bot</a>&nbsp;to your account.To verify the setup, on a separate branch, write tests to cover the lines that have not been covered:</li>
</ul>
<pre><code class="lang-C++ hljs"><span class="hljs-selector-tag">TEST_METHOD</span>(<span class="hljs-selector-tag">IsNegativePowerOfTwo</span>)
{
    <span class="hljs-attribute">Assert</span>::<span class="hljs-built_in">IsFalse</span>(is_power_of_two(<span class="hljs-number">-8</span>));
}
</code></pre>
<p>Push and create a pull request from the branch. You should see a report like below on the pull request when the actions complete:</p>
<p><img src="images/wQh4cVS.png" alt="PR comment"></p>
<p>Observe that coverage increases as expected.</p>
<h2 id="conclusion">Conclusion</h2>
<p>Code coverage is vital to ensuring that your software quality stays consistent over time. Now you should have a good grasp of how to integrate C++ code coverage reports in your CI workflows with Codecov in order to ensure you won’t fall behind on your coverage.</p>
<p>Although the tutorial was specifically for Windows, Codecov is platform-agnostic and can be configured not only with other C++ toolchains but also other languages and code-hosting platforms.</p>
